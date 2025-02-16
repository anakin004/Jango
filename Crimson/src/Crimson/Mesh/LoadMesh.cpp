
#include "cnpch.h"
#include "LoadMesh.h"
#include "Crimson/Core/Log.h"

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Crimson/Renderer/Material.h"
#include "Crimson/Core/UUID.h"
#include "Crimson/Scene/SceneSerializer.h"
#include "Crimson/Core/ResourceManager.h"

namespace Crimson
{
	LoadMesh::LoadMesh()
	{
	}

	LoadMesh::LoadMesh(const std::string& Path, LoadType type)
	{
		GlobalTransform = glm::mat4(1.0);
		std::filesystem::path mesh_path(Path);
		objectName = mesh_path.stem().string();
		m_Path = (mesh_path.parent_path() / mesh_path.stem()).string() + extension; //temporary

		if (m_LOD.size() == 0)
			m_LOD.push_back(this);

		if (type == LOAD_MESH)
		{
			LoadObj(Path);
		}
		if (type == IMPORT_MESH)
		{
			SceneSerializer deserialize;
			deserialize.DeSerializeMesh(m_Path, *this);
			uuid = UUID(Path); //only create uuid for engine compatible mesh
			//ResourceManager::allMeshes[uuid] = m_Mesh;
			CreateStaticBuffers();
		}
	}
	LoadMesh::~LoadMesh()
	{
	}
	void LoadMesh::LoadObj(const std::string& Path)
	{
		Assimp::Importer importer;

		static const uint32_t s_MeshImportFlags =
			aiProcess_CalcTangentSpace
			| aiProcess_Triangulate
			| aiProcess_JoinIdenticalVertices
			| aiProcess_SortByPType
			| aiProcess_GenNormals
			| aiProcess_GenUVCoords
			| aiProcess_LimitBoneWeights
			| aiProcess_ValidateDataStructure
			| aiProcess_GlobalScale
			| aiProcess_OptimizeMeshes
			| aiProcess_OptimizeGraph;

		const aiScene* scene = importer.ReadFile(Path, s_MeshImportFlags);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			CN_CORE_ERROR("Assimp Error: ", importer.GetErrorString());
			return;
		}

		ProcessMaterials(scene);
		ProcessNode(scene->mRootNode, scene);
		ProcessMesh();
		CreateStaticBuffers();

		m_Mesh.clear();
		m_Mesh.shrink_to_fit();
	}

	void LoadMesh::CreateLOD(const std::string& Path, LoadType type)
	{
		m_LOD.push_back(new LoadMesh(Path, type));
	}

	LoadMesh* LoadMesh::GetLOD(int lodIndex)
	{
		if (lodIndex < m_LOD.size() && lodIndex >= 0)
			return m_LOD[lodIndex];
		else
			return m_LOD[m_LOD.size() - 1]; //if lod not available give the highest LOD
	}

	auto AssimpToGlmMatrix = [&](const aiMatrix4x4& from) {
		glm::mat4 to;
		to[0][0] = from.a1; to[0][1] = from.a2; to[0][2] = from.a3; to[0][3] = from.a4;
		to[1][0] = from.b1; to[1][1] = from.b2; to[1][2] = from.b3; to[1][3] = from.b4;
		to[2][0] = from.c1; to[2][1] = from.c2; to[2][2] = from.c3; to[2][3] = from.c4;
		to[3][0] = from.d1; to[3][1] = from.d2; to[3][2] = from.d3; to[3][3] = from.d4;

		return std::move(to);
	};

	void LoadMesh::ProcessNode(aiNode* Node, const aiScene* scene)
	{
		GlobalTransform *= AssimpToGlmMatrix(Node->mTransformation);
		for (int i = 0; i < Node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[Node->mMeshes[i]];
			m_Mesh.push_back(mesh);
		}

		for (int i = 0; i < Node->mNumChildren; i++)
		{
			ProcessNode(Node->mChildren[i], scene);
		}


	}
	void LoadMesh::ProcessMesh()
	{
		for (int i = 0; i < m_Mesh.size(); i++)
		{
			unsigned int MaterialIdx = m_Mesh[i]->mMaterialIndex;
			m_SubMeshes[MaterialIdx].NumVertices = m_Mesh[i]->mNumVertices;

			m_SubMeshes[MaterialIdx].Vertices.reserve(m_Mesh[i]->mNumVertices);
			m_SubMeshes[MaterialIdx].TexCoord.reserve(m_Mesh[i]->mNumVertices);
			m_SubMeshes[MaterialIdx].Normal.reserve(m_Mesh[i]->mNumVertices);
			m_SubMeshes[MaterialIdx].Tangent.reserve(m_Mesh[i]->mNumVertices);
			m_SubMeshes[MaterialIdx].BiTangent.reserve(m_Mesh[i]->mNumVertices);
			m_SubMeshes[MaterialIdx].Indices.reserve(m_Mesh[i]->mNumVertices);



			for (int k = 0; k < m_Mesh[i]->mNumVertices; k++)
			{

				aiVector3D aivertice = m_Mesh[i]->mVertices[k];
				glm::vec4 pos = GlobalTransform * glm::vec4(aivertice.x, aivertice.y, aivertice.z, 1.0);
				Bounds SubMeshBounds(glm::vec3(pos.x, pos.y, pos.z));
				m_SubMeshes[MaterialIdx].MeshBounds.Union(SubMeshBounds);
				m_SubMeshes[MaterialIdx].Vertices.push_back({ pos.x,pos.y,pos.z });

				if (m_Mesh[i]->mTextureCoords[0])
				{
					glm::vec2 coord(0.0f, 0.0f);
					coord.x = m_Mesh[i]->mTextureCoords[0][k].x;
					coord.y = m_Mesh[i]->mTextureCoords[0][k].y;

					m_SubMeshes[MaterialIdx].TexCoord.push_back(coord);
				}
				else
					m_SubMeshes[MaterialIdx].TexCoord.emplace_back(0.0f,0.0f);


				if (m_Mesh[i]->HasNormals()) {
					aiVector3D ainormal = m_Mesh[i]->mNormals[k];
					glm::vec4 norm = GlobalTransform * glm::vec4(ainormal.x, ainormal.y, ainormal.z, 0.0);
					m_SubMeshes[MaterialIdx].Normal.push_back({ norm.x,norm.y,norm.z });
				}


				if (m_Mesh[i]->HasTangentsAndBitangents())
				{
					aiVector3D tangent = m_Mesh[i]->mTangents[k];
					aiVector3D bitangent = m_Mesh[i]->mBitangents[k];
					glm::vec4 tan = GlobalTransform * glm::vec4(tangent.x, tangent.y, tangent.z, 0.0);
					glm::vec4 bitan = GlobalTransform * glm::vec4(bitangent.x, bitangent.y, bitangent.z, 0.0);

					m_SubMeshes[MaterialIdx].Tangent.emplace_back( tan.x, tan.y, tan.z );
					m_SubMeshes[MaterialIdx].BiTangent.emplace_back( bitan.x,bitan.y,bitan.z );
				}
				else
				{
					m_SubMeshes[MaterialIdx].Tangent.emplace_back( 0.0f,0.0f,0.0f );
					m_SubMeshes[MaterialIdx].BiTangent.emplace_back( 0.0f,0.0f,0.0f );
				}
			}

			m_SubMeshes[MaterialIdx].NumIndices = m_Mesh[i]->mNumFaces * static_cast<uint32_t>(3);
			
			for (unsigned int j = 0; j < m_Mesh[i]->mNumFaces; j++) 
			{
				aiFace& face = m_Mesh[i]->mFaces[j];
				m_SubMeshes[MaterialIdx].Indices.push_back(face.mIndices[0]);
				m_SubMeshes[MaterialIdx].Indices.push_back(face.mIndices[1]);
				m_SubMeshes[MaterialIdx].Indices.push_back(face.mIndices[2]);
			}
			
			total_bounds.Union(m_SubMeshes[MaterialIdx].MeshBounds);

		}

	}
	void LoadMesh::ProcessMaterials(const aiScene* scene)//get all the materials in a scene
	{
		int NumMaterials = scene->mNumMaterials;
		m_SubMeshes.resize(NumMaterials);

		const std::string relative_path = "Assets/Textures/MeshTextures/";
		auto GetTexturePath = [&](aiMaterial*& material, aiTextureType type)
		{
			auto x = material->GetTextureCount(type);
			if (x > 0)
			{
				aiString str;
				material->GetTexture(type, 0, &str);
				std::string absolute_path = str.data;

				return (relative_path + absolute_path.substr(absolute_path.find_last_of("\\") + 1));
			}
			return std::string("");
		};
		for (int i = 0; i < NumMaterials; i++)
		{
			aiMaterial* scene_material = scene->mMaterials[i];
			std::string materialName = objectName + std::string("_") + std::string(scene_material->GetName().C_Str());
			Ref<Material> material = Material::Create(materialName, ""); //create a material and set the default storage directory
			m_SubMeshes[i].MaterialID = material->materialID;

			//if material cannot be found then create and serialize the material
			if (ResourceManager::allMaterials.find(material->materialID) == ResourceManager::allMaterials.end())
			{
				std::string diffuse_path = GetTexturePath(scene_material, aiTextureType_DIFFUSE);
				std::string normal_path = GetTexturePath(scene_material, aiTextureType_NORMALS);
				std::string roughness_path = GetTexturePath(scene_material, aiTextureType_SHININESS);

				material->SetTexturePaths(diffuse_path, normal_path, roughness_path);
				material->SerializeMaterial("", materialName); //save the material
			}
		}



	}
	void LoadMesh::CalculateTangent()
	{
		glm::vec3 tangent = { 0.f,0.f,0.f };

	}
	void LoadMesh::CreateStaticBuffers()
	{

		for (int k = 0; k < m_SubMeshes.size(); k++)
		{
			std::vector<VertexAttributes> buffer(m_SubMeshes[k].Vertices.size());
			m_SubMeshes[k].VertexArray = VertexArray::Create();

			// Populate vertex buffer
			for (int i = 0; i < m_SubMeshes[k].Vertices.size(); i++)
			{
				glm::vec3 transformed_normals = m_SubMeshes[k].Normal[i];
				glm::vec3 transformed_tangents = m_SubMeshes[k].Tangent[i];
				glm::vec3 transformed_binormals = m_SubMeshes[k].BiTangent[i];
				buffer[i] = VertexAttributes(glm::vec4(m_SubMeshes[k].Vertices[i], 1.0), m_SubMeshes[k].TexCoord[i], transformed_normals, transformed_tangents, transformed_binormals);
			}

			// Create and set vertex buffer
			vb = VertexBuffer::Create(&buffer[0].Position.x, sizeof(VertexAttributes) * m_SubMeshes[k].Vertices.size());
			ib = IndexBuffer::Create(m_SubMeshes[k].Indices.data(), m_SubMeshes[k].Indices.size() * sizeof(unsigned int));


			bl = std::make_shared<BufferLayout>();
			bl->push("Position", ShaderDataType::Float4);
			bl->push("TexCoord", ShaderDataType::Float2);
			bl->push("Normal", ShaderDataType::Float3);
			bl->push("Tangent", ShaderDataType::Float3);
			bl->push("BiTangent", ShaderDataType::Float3);

			m_SubMeshes[k].VertexArray->SetIndexBuffer(ib);
			m_SubMeshes[k].VertexArray->AddBuffer(bl, vb);



		}
	}

}
