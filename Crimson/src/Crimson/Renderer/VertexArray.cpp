#include "cnpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Crimson {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
		case RendererAPI::API::OpenGL:		return MakeRef<OpenGLVertexArray>();
		}

		CN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


}