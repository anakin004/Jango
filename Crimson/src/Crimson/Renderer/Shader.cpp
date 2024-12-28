#include "cnpch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Crimson {


	Ref<Shader> Shader::Create(const std::string& filename)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:			CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
		case RendererAPI::API::OpenGL:			return   MakeRef<OpenGLShader>(filename);
		}

		CN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


}
