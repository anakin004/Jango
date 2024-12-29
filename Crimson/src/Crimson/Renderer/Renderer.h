#pragma once

#include "RenderCommand.h"
#include "RendererAPI.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Crimson {


	class Renderer {
	public:

		static void Init();
		
		static void OnWindowResize(uint32_t width, uint32_t height);
		
		static void BeginScene(OrthographicCamera& camera); // add scene parameters
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const crm::mat4& transformMatrix = crm::mat4(1.0f));

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:

		struct SceneData
		{
			crm::mat4 ViewProjectionMatrix;
		};
		
		static Scope<SceneData> m_SceneData;
	};
}
