#pragma once
#include "Crimson/Renderer/Buffer.h"
#include "Crimson/Renderer/Shader.h"
#include "Crimson/Renderer/RenderCommand.h"

namespace Crimson {
	class CubeMapEnvironment {
	public:
		static void Init(const std::string& path);
		static void RenderCubeMap(const glm::mat4& view, const glm::mat4& proj, const glm::vec3& view_dir);
		static void RenderQuad(const glm::mat4& view, const glm::mat4& proj);//used for cube-maps (direction is passed in 2nd slot)
		static void RenderQuad();//used for 2D-Textures (Texture-coordinate is passed in 2nd slot)
	private:
		static uint32_t irradiance_map_id, tex_id;
		static uint32_t framebuffer_id, framebuffer_id2;
		static uint32_t hdrMapID;
		static uint32_t renderBuffer_id;
		static uint32_t captureRes;
		static Ref<Shader> Cube_Shader, irradiance_shader, equirectangularToCube_shader, prefilterShader, BRDFSumShader;
	private:
		static void SwitchToFace(int n, float& pitch, float& yaw);
		static void ConstructIrradianceMap(const glm::mat4& proj);
		static void CreateSpecularMap(const glm::mat4& proj,glm::mat4*);
	};
}