#include "cnpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Crimson/Core/Core.h"

namespace Crimson {


	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		// I will not be seperating
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:			CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
		case RendererAPI::API::OpenGL:			return   MakeRef<OpenGLVertexBuffer>(vertices, size);
		}

		CN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:			CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
		case RendererAPI::API::OpenGL:		return MakeRef<OpenGLIndexBuffer>(indices, count);
		}

		CN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
