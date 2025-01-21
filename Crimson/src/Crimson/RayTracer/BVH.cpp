#include "cnpch.h"
#include "BVH.h"
#include "Crimson/Core/Core.h"
#include <Glad/glad.h>
#include "Crimson/Core/ResourceManager.h"
#include <GLFW/glfw3.h>

constexpr uint_8 NUM_BINS 200


namespace Crimson
{
	static int val = 0;
	BVH::BVH(LoadMesh*& mesh)
		m_Mesh(mesh), m_NumNodes(0)
	{
		uint32_t rootIndex = 0;
		const glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), { 0.f,0.f,1.f }) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		CN_CORE_TRACE("Creating Triangles : BVH")
		CreateTriangles(transform);
		CN_CORE_TRACE("Created Triangles ... Updating Materials : BVH")
		UpdateMaterials();
		CN_CORE_TRACE("Updated Materials : BVH")
		
		triIndex.resize(RTTrianglesArr.size()); //making a seperate triangle index for swaping
		for (int i = 0; i < RTTrianglesArr.size(); i++)
			TriIndices[i] = i;
		
		arrLinearBVHNode.resize(arrRTTriangles.size() * 2 + 1);
		CN_CORE_TRACE("BVH Creation started")
		BuildBVH(m_Head, 0, RTTrianglesArr.size());
		CleanBVH(m_Head);//identify child nodes by making their triangle count = 0
		FlattenBVH(m_Head, m_NumNodes);
		arrLinearBVHNode.resize(m_NumNodes);

		CN_CORE_INFO("BVH Initialized!")

		CN_CORE_INFO("Number of triangles before BVH construction: {0}", RTTrianglesArr.size());
		CN_CORE_INFO("Number of triangles after BVH construction: {0}", m_NumNodes);
	}
	void BVH::CreateTriangles(glm::mat4& transform)
	{
		int matCount = 0;
		std::vector<std::string> AlbedoPaths, RoughnessPaths; 
		for (auto& sub_mesh : m_Mesh->m_subMeshes)
		{
			Ref<Texture2D> AlbedoTexture = Texture2D::Create(ResourceManager::allMaterials[sub_mesh.m_MaterialID]->GetAlbedoPath());
			Ref<Texture2D> RoughnessTexture = Texture2D::Create(ResourceManager::allMaterials[sub_mesh.m_MaterialID]->GetRoughnessPath());

			//Enabling bindless textures causes render-doc to crash so disable them
			uint64_t AlbedoHandle = glGetTextureHandleARB(AlbedoTexture->GetID()); //get a handle from the gpu
			glMakeTextureHandleResidentARB(AlbedoHandle); //load the texture into gpu memory using the handle
			uint64_t RoughnessHandle = glGetTextureHandleARB(RoughnessTexture->GetID());
			if(AlbedoHandle!=RoughnessHandle)
				glMakeTextureHandleResidentARB(RoughnessHandle);

			for (int i = 0; i < sub_mesh.Vertices.size(); i += 3)
			{

				//transforming the vertices and normals to world space
				glm::vec3 v0 = transform * glm::vec4(sub_mesh.Vertices[i], 1.0f);
				glm::vec3 v1 = transform * glm::vec4(sub_mesh.Vertices[i + 1], 1.0f);
				glm::vec3 v2 = transform * glm::vec4(sub_mesh.Vertices[i + 2], 1.0f);

				glm::vec3 n0 = transform * glm::vec4(sub_mesh.Normal[i], 1.0f);
				glm::vec3 n1 = transform * glm::vec4(sub_mesh.Normal[i + 1], 1.0f);
				glm::vec3 n2 = transform * glm::vec4(sub_mesh.Normal[i + 2], 1.0f);

				RTTriangles triangles(v0, v1, v2, n0, n1, n2, sub_mesh.TexCoord[i], sub_mesh.TexCoord[i + 1], sub_mesh.TexCoord[i + 2], matCount);
				triangles.TexAlbedo = AlbedoHandle;
				triangles.TexRoughness = RoughnessHandle;

				RTTrianglesArr.push_back(triangles);
			}

			matCount++; //increment the material as we move to the next sub mesh

			CN_CORE_TRACE("Made Material");
		}
		MaterialsArr.resize(matCount);
		
	}

	void BVH::UpdateMaterials()
	{
		int k = 0;
		for (auto sub_mesh : m_Mesh->m_subMeshes) //iterate through all sub meshes and get the materials
		{
			CN_CORE_TRACE("Updating Material, Count : {0}", k);
			CN_ASSERT(ResourceManager::allMaterials[sub_mesh.m_MaterialID], "Resource Manager Invalid (BVH)");
			auto ResourceMaterial = ResourceManager::allMaterials[sub_mesh.m_MaterialID];
			Material mat;
			mat.color = ResourceMaterial->GetColor();
			mat.emissive_col = ResourceMaterial->GetColor(); //needs change
			mat.emissive_strength ResourceMaterial->GetEmission(); //needs change
			mat.metalness = ResourceMaterial->GetMetalness();
			mat.roughness = ResourceMaterial->GetRoughness();
			arrMaterials[k] = mat;
			k++;
		}
	}

	float BVH::EvaluateSAH(BVHNode& node, int& axis, float& pos)
	{
		float best_cost = std::numeric_limits<float>::max();
		Bounds ResultingBound; //get the total bounds of all the triangles in a particular node
		for (int i = 0; i < node.TriangleCount; i++)
		{
			Bounds bnds = (RTTrianglesArr[TriIndices[node.TriangleStartID + i]].GetBounds());

			// adding node bound to resulting bound
			ResultingBound.Union(bnds);
		}

		for (int a = 0; a < 3; a++) //iterate through all the axises
		{

			if (ResultingBound.aabbMax[a] == ResultingBound.aabbMin[a])
				continue;

			Bins bins[NUM_BINS]; //create bins array to store the triangle count and the bounds of the triangles in a node
			auto size = (ResultingBound.aabbMax[a] - ResultingBound.aabbMin[a]) / NUM_BINS; //get size of individual bin
			for (int i = 0; i < node.TriangleCount; i++)
			{
				auto& triangle = RTTrianglesArr[TriIndices[node.TriangleStartID + i]];
				//get the bin index
				int binIndx = std::min(NUM_BINS - 1,
					static_cast<int>(std::abs((triangle.GetCentroid()[a] - ResultingBound.aabbMin[a]) / size)));
				bins[binIndx].TriangleCount++;
				bins[binIndx].bounds.Union(triangle.GetBounds());
			}

			// determine triangle counts and bounds for this split candidate
			Bounds leftBox, rightBox;
			int leftTriangleCount[NUM_BINS - 1], rightTriangleCount[NUM_BINS - 1]; //containers to store the total triangle count and area on left side of the split plane
			float leftSurfaceArea[NUM_BINS - 1], rightSurfaceArea[NUM_BINS - 1]; //containers to store the total triangle count and area on right side of the split plane
			int leftCount = 0, rightCount = 0;
			for (uint32_t i = 0; i < NUM_BINS - 1; i++) //accumulate the triangle count and box area.
			{
				leftCount += bins[i].TriangleCount;
				leftBox.Union(bins[i].bounds);
				leftTriangleCount[i] = leftCount;
				leftSurfaceArea[i] = leftBox.area(); //fill from first to last

				rightCount += bins[NUM_BINS - 1 - i].TriangleCount;
				rightBox.Union(bins[NUM_BINS - 1 - i].bounds);
				rightTriangleCount[NUM_BINS - 2 - i] = rightCount;
				rightSurfaceArea[NUM_BINS - 2 - i] = rightBox.area(); //fill from last to first
			}

			for (uint32_t i = 0; i < NUM_BINS - 1; i++) //evaluate cost using surface area heuristic
			{
				float cost = leftTriangleCount[i] * leftSurfaceArea[i] + rightTriangleCount[i] * rightSurfaceArea[i];
				if (cost < best_cost)
				{
					best_cost = cost;
					axis = a;
					pos = m_Bounds.aabbMin[a] + (i + 1) * size;
				}
			}
		}
		return best_cost > 0 ? best_cost : 1e30f;
	}

	int BVH::FlattenBVH(BVHNode* node, int* offset)//dfs traversal
	{
		LinearBVHNode* linearNode = &arrLinearBVHNode[*offset];
		linearNode->aabbMax = node->aabbMax;
		linearNode->aabbMin = node->aabbMin;

		int myOffset = (*offset)++;

		if (node->TriangleCount > 0) 
		{
			// If the node has triangles, assign them to this node
			linearNode->TriangleStartID = node->TriangleStartID;
			linearNode->TriangleCount = node->TriangleCount;
		}

		else 
		{
			linearNode->TriangleStartID = node->TriangleStartID;
			linearNode->TriangleCount = node->TriangleCount;

			BVH::FlattenBVH(node->LeftChild, offset);
			linearNode->RightChild = BVH::FlattenBVH(node->RightChild, offset);
		}

		return myOffset;
	}

	void BVH::CleanBVH(BVHNode* node)
	{
		if (node->LeftChild == nullptr && node->RightChild == nullptr)
		{
			return;
		}
		else
		{
			node->TriangleCount = 0;
			if (node->LeftChild)
				CleanBVH(node->LeftChild);
			if (node->RightChild)
				CleanBVH(node->RightChild);
		}
	}

	//recursively building the bvh tree and storing it as dfs format
	void BVH::BuildBVH(BVHNode*& node, int triStartID, int triCount)
	{
		node = new BVHNode();
		//++numNodes;
		Bounds bounds;
		for (int i = 0; i < triCount; i++)
		{
			auto bnds = RTTrianglesArr[TriIndices[i + triStartID]].GetBounds();
			bounds.Union(bnds);
		}

		node->aabbMax = bounds.aabbMax;
		node->aabbMin = bounds.aabbMin;
		node->TriangleStartID = triStartID;
		node->TriangleCount = triCount;

		int bestAxis = -1;
		float bestPos = 0, bestCost = 1e30f;

		bestCost = EvaluateSAH(*node, bestAxis, bestPos);

		node->Axis = bestAxis;//net the node axis
		if (triCount <= 2)//2 is the minimum number of triangles that a node should contain
		{
			return;
		}

		int axis = bestAxis;
		glm::vec3 extent = bounds.aabbMax - bounds.aabbMin;
		float splitPos = bestPos;

		float parentArea = extent.x * extent.y + extent.y * extent.z + extent.z * extent.x;
		float parentCost = triCount * parentArea;
		if (bestCost >= parentCost)
			return;

		int i = TriStartID, j = i + TriCount - 1;
		//do partial sorting
		while (i <= j)
		{
			if (RTTrianglesArr[TriIndices[i]].GetCentroid()[axis] < splitPos)
				i++;
			else
				std::swap(TriIndices[i], TriIndices[j--]);
		}

		int leftCount = i - triStartID;
		if (leftCount == 0 || leftCount == triCount)
		{
			return;
		}
		BVH::BuildBVH(node->LeftChild, triStartID, leftCount);
		BVH::BuildBVH(node->RightChild, i, triCount - leftCount);
	}
}
