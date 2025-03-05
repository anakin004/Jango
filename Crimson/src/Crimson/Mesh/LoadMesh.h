#pragma once

#include "Crimson.h"
#include <fstream>
#include <sstream>
#include <vector>

//forward declarations

struct aiMesh;
struct aiNode;
struct aiScene;

namespace Crimson {

	class Texture2DArray;
	class Material;

	struct Bounds
	{
		glm::vec3 aabbMax, aabbMin;
		Bounds() {
			float minNum = std::numeric_limits<float>::lowest();
			float maxNum = std::numeric_limits<float>::max();
			aabbMin = glm::vec3(maxNum, maxNum, maxNum);
			aabbMax = glm::vec3(minNum, minNum, minNum);
		}
		Bounds(glm::vec3& p)
		{
			aabbMax = p;
			aabbMin = p;
		}
		Bounds(glm::vec3& min, glm::vec3& max)
		{
			aabbMax = max;
			aabbMin = min;
		}
		Bounds(glm::vec3& a, glm::vec3& b, glm::vec3& c)
		{
			aabbMax = glm::max(glm::max(a, b), c);
			aabbMin = glm::min(glm::min(a, b), c);
		}
		void Union(const Bounds& bounds)
		{
			aabbMax = glm::max(aabbMax, bounds.aabbMax);
			aabbMin = glm::min(aabbMin, bounds.aabbMin);
		}
		float area() //get surface area of the box
		{
			glm::vec3 e = aabbMax - aabbMin; // box extent
			return e.x * e.y + e.y * e.z + e.z * e.x;
		}
		glm::vec3 GetMidPoint()
		{
			return (aabbMax + aabbMin) / glm::vec3(2.0);
		}
	};




	struct SubMesh
	{
		std::vector<glm::vec3> Vertices;
		std::vector<glm::vec3> Normal;
		std::vector<glm::vec3> Tangent;
		std::vector<glm::vec3> BiTangent;
		std::vector<glm::vec2> TexCoord;
		std::vector<unsigned int> Indices;
		Ref<VertexArray> VertexArray;
		uint64_t MaterialID;
		uint32_t NumVertices;
		uint32_t NumIndices;
		Bounds MeshBounds; //submesh bounds utilized by BVH

	};




	class LoadMesh
	{
	public:

		enum LoadType
		{
			IMPORT_MESH, LOAD_MESH
		};

	public:

		LoadMesh();
		LoadMesh(const std::string& Path, LoadType type = LoadType::LOAD_MESH);
		~LoadMesh();
		void CreateLOD(const std::string& Path, LoadType type = LoadType::LOAD_MESH);
		LoadMesh* GetLOD(int lodIndex);

	public:

		std::string m_Path;
		std::vector<SubMesh> m_SubMeshes;
		Bounds total_bounds; //total mesh bounds
		glm::mat4 GlobalTransform;
		uint64_t uuid;

	private:

		std::string extension = ".asset";
		std::string objectName;
		std::vector<LoadMesh*> m_LOD;
		Ref<BufferLayout> bl;
		Ref<VertexBuffer> vb;
		Ref<IndexBuffer> ib;
		std::vector<aiMesh*> m_Mesh;
		struct VertexAttributes {
			//glm::vec3 Position;
			glm::vec4 Position;
			glm::vec2 TextureCoordinate;
			glm::vec3 Normal;
			glm::vec3 Tangent;
			glm::vec3 BiNormal;

			VertexAttributes() = default;
			VertexAttributes(const glm::vec4& Position, const glm::vec2& TextureCoordinate, const glm::vec3& normal = { 0,0,0 }, const glm::vec3& Tangent = { 0,0,0 }, const glm::vec3& BiNormal = { 0,0,0 })
				: Position(Position), TextureCoordinate(TextureCoordinate), Normal(normal), Tangent(Tangent), BiNormal(BiNormal)
			{
			}
		};

	private:

		void LoadObj(const std::string& Path);
		void ProcessNode(aiNode* Node, const aiScene* scene);
		void ProcessMesh();
		void ProcessMaterials(const aiScene* scene);
		void CreateStaticBuffers();

	};
}
