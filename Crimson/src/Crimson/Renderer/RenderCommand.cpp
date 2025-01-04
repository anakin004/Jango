#include "cnpch.h"
#include "RenderCommand.h"


#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Crimson {

	Scope<RendererAPI> RenderCommand::s_RendererAPI =  MakeScope<OpenGLRendererAPI>();
	
	void RenderCommand::SetViewport(unsigned int Width, unsigned int Height)
	{
		m_RendererAPI->SetViewPort(Width, Height);
	}

	Ref<RendererAPI> RenderCommand::GetRendererAPI()
	{
		switch (RendererAPI::GetAPI()) {
		case GraphicsAPI::None:
			return nullptr;
		case GraphicsAPI::OpenGL:
			return std::make_shared<OpenGlRendererAPI>();
		default:
			CN_CORE_ERROR("No valid Graphics api");
			return nullptr;
		}
	}
}