#include "cnpch.h"
#include "RenderCommand.h"


#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Crimson {

	// lasts entire duration of the program, no need to worry about memory leaks
	// its only going to be 8 bytes, would be 1 but there is a v-table

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
	
}