#include "cnpch.h"
#include "Renderer.h"
#include "Renderer3D.h"
#include "Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Crimson {


	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
		Renderer3D::Init();
		CN_CORE_INFO("Renderer2D and Renderer3D Initialized!");
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
		Renderer3D::Shutdown();
		CN_CORE_INFO("Renderer2D and Renderer3D Shutdown!");
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}


}
