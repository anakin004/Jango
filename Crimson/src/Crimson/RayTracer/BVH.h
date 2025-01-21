#pragma once

#include "Crimson.h"

namespace Crimson
{
	class BVH
	{
	public:
		
		enum SplitMethod
                {
                        SAH, 
			MEAN
                };

		struct RTTriangles
		{
			glm::vec3 v0, v1, v2;
			glm::vec3 n0, n1, n2;
			glm::vec2 uv0, uv1, uv2;
			uint64_t TexAlbedo; //handle value for bindless albedo texture
			uint64_t TexRoughness; //handle value for bindless roughness texture
			int MaterialID;

			//int materialID;
			RTTriangles() = default;
			RTTriangles(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2, glm::vec3& n0, glm::vec3& n1, glm::vec3& n2,
				glm::vec2& uv0, glm::vec2& uv1, glm::vec2& uv2, int materialID)
				: v0(v0), v1(v1), v2(v2), n0(n0), n1(n1), n2(n2), uv0(uv0), uv1(uv1), uv2(uv2), MaterialID(materialID)
			{
			}
			glm::vec3 GetCentroid() { return (v0 + v1 + v2) * 0.3333333333333f; };
			Bounds GetBounds() { return Bounds(v0, v1, v2); };
		};
		struct BVHNode
		{
			BVHNode* LeftChild, * RightChild;
			int Axis;
			int TriangleStartID, TriangleCount;
			glm::vec3 aabbMin, aabbMax;//bounds of the node
			BVHNode() : LeftChild(nullptr), RightChild(nullptr), TriangleStartID(0), TriangleCount(0)  {}
		};
		struct LinearBVHNode
		{
			int RightChild;
			int TriangleStartID, TriangleCount;
			glm::vec3 aabbMin, aabbMax;
		};
		struct Bins
		{
			Bounds bounds;
			int TriangleCount = 0;
		};
		struct Material
		{
			glm::vec4 Color;
			float Roughness;
			float Metalness;
			glm::vec4 EmissiveCol;
			float EmmisiveStrength;
		};
	public:
		BVH() = default;
		BVH(LoadMesh*& mesh);
		void UpdateMaterials();
	private:
		void BuildBVH(BVHNode*& node, int triStartID, int triCount);
		void CreateTriangles(glm::mat4& transform = glm::mat4(1.0)); //create triangles from mesh vertex positions
		float EvaluateSAH(BVHNode& node, int& axis, float& pos); //returns cost after finding best axis and position
		int FlattenBVH(BVHNode* node, int* offset);
		void CleanBVH(BVHNode* node);//removes count of triangles from child nodes


	public:
		std::vector<Material> MaterialArr;
		std::vector<Ref<Texture2D>> TexAlbedoArr;
		std::vector<Ref<Texture2D>> TexRoughnessArr;

		std::vector<LinearBVHNode> LinearBVHNodeArr;//to be sent on to the gpu
		std::vector<RTTriangles> RTTrianglesArr;//to be sent on to the gpu
		std::vector<int> TriIndices;//to be sent on to the gpu
		
		int m_NumNodes = 0;

	private:
		LoadMesh* m_Mesh = nullptr;
		BVHNode* m_Head = nullptr;
	};
}
