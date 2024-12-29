#pragma once

#include "RenderCommand.h"
#include "RendererAPI.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Crimson {


	class Renderer3D {
	public:

		static void Init();
		static void Shutdown();
	
		
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
