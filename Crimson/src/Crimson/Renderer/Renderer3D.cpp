#include "cnpch.h"
#include "Renderer3D.h"
#include "Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Crimson {

	Scope<Renderer3D::SceneData> Renderer3D::m_SceneData = MakeScope<Renderer3D::SceneData>();
		
	void Renderer3D::Init()
	{
	}

	void Renderer3D::Shutdown()
	{
	}


	void Renderer3D::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer3D::EndScene()
	{

	}

	void Renderer3D::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const crm::mat4& transformMatrix)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transformMatrix);
		RenderCommand::DrawIndexed(vertexArray);
	}

}
