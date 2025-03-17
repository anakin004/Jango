#include "cnpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "Crimson/Core/Core.h"

namespace Crimson {


	Ref<VertexBuffer> VertexBuffer::Create(const float* vertices, size_t size)
	{
		// I will not be seperating
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::None:			CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
		case GraphicsAPI::OpenGL:			return   MakeRef<OpenGLVertexBuffer>(vertices, size);
		}

		CN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	Ref<VertexBuffer> VertexBuffer::Create(size_t size, BufferStorageType type)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::None:			CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
		case GraphicsAPI::OpenGL:			return   MakeRef<OpenGLVertexBuffer>(size, type);
		}

		CN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(const uint32_t* indices, size_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::None:			CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
		case GraphicsAPI::OpenGL:		return MakeRef<OpenGLIndexBuffer>(indices, size);
		}

		CN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	/// ////////////////////////////////////////////////////////////////////////////

	void BufferLayout::push(std::string name, ShaderDataType type)
	{
		m_Elements.push_back(new BufferElements(name, type));
		Stride += GetSize(type);
	}
	unsigned int BufferLayout::GetSize(ShaderDataType type)
	{
		switch (type) {
		case ShaderDataType::Float: return sizeof(float);
		case ShaderDataType::Float2: return sizeof(float) * 2;
		case ShaderDataType::Float3: return sizeof(float) * 3;
		case ShaderDataType::Float4: return sizeof(float) * 4;
		case ShaderDataType::Int: return sizeof(int);
		case ShaderDataType::Int2: return sizeof(int) * 2;
		case ShaderDataType::Int3: return sizeof(int) * 3;
		case ShaderDataType::Int4: return sizeof(int) * 4;
		case ShaderDataType::Mat2: return sizeof(float) * 2 * 2;
		case ShaderDataType::Mat3: return sizeof(float) * 3 * 3;
		case ShaderDataType::Mat4: return sizeof(float) * 4 * 4;
		default:
			CN_CORE_ERROR("Unidentfied Type");
		}

	}

	/////////////////////////////////////////////////////////////////////////

	Ref<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI()) {
		case GraphicsAPI::OpenGL:
			return MakeRef<OpenGLVertexArray>();
		case GraphicsAPI::None:
			CN_CORE_ERROR("NOT A VALID GRAPHICS API");
			break;
		default:
			CN_CORE_ERROR("GRAPHICS API DOESNOT MATCHES THE GIVEN API LIST");
		}
		return nullptr;
	}

}
