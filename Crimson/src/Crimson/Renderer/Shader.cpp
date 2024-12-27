#include "cnpch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Crimson {


	Shader* Shader::Create(const std::string& filename)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:			CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
		case RendererAPI::OpenGL:		return new OpenGLShader(filename);
		}

		CN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


}
