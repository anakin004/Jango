#include "cnpch.h"
#include "RenderCommand.h"


#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Crimson {

	Scope<RendererAPI> RenderCommand::s_RendererAPI =  MakeScope<OpenGLRendererAPI>();
	
}