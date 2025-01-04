#include "cnpch.h"

#include "OpenGLBuffer.h"
#include "Crimson/Renderer/Renderer2D.h"
#include <Glad/glad.h>

namespace Crimson {

	////////////////////////////////////////////////////////
/// Vertex Buffer //////////////////////////////////////
//////////////////////////////////////////////////////


	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, size_t size)
	{
		glGenBuffers(1, &m_RendererID);//set up vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, BufferStorageType Storage_Type)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		auto flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
		switch (Storage_Type)
		{
		case BufferStorageType::MUTABLE:
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
			break;
		case BufferStorageType::IMMUTABLE:
			glBufferStorage(GL_ARRAY_BUFFER, size, 0, flags);
			break;
		default:
			CN_CORE_ERROR("Select correct storage type");
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
			break;
		}
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(size_t size, const void* data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void* OpenGLVertexBuffer::MapBuffer(size_t size)
	{
		auto flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
		return glMapBufferRange(GL_ARRAY_BUFFER, 0, size, flags);
	}

	////////////////////////////////////////////////////////
	/// Index Buffer //////////////////////////////////////
	//////////////////////////////////////////////////////


	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* data, size_t size)
	{
		m_Elements = size / sizeof(unsigned int);
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	size_t OpenGLIndexBuffer::GetCount()
	{
		return m_Elements;
	}

// 	// --------------------------------------------------------------------
// 	//							Vertex Buffer
// 	// --------------------------------------------------------------------
// 
// 	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
// 	{
// 		CN_PROFILE_FUNCTION();
// 
// 		glCreateBuffers(1, &m_RendererID);
// 		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
// 		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
// 	}
// 
// 
// 	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
// 	{
// 		CN_PROFILE_FUNCTION();
// 
// 		glCreateBuffers(1, &m_RendererID);
// 		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
// 		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
// 	}
// 
// 	OpenGLVertexBuffer::~OpenGLVertexBuffer()
// 	{
// 		CN_PROFILE_FUNCTION();
// 
// 		glDeleteBuffers(1, &m_RendererID);
// 	}
// 
// 	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
// 	{
// 		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
// 		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
// 	}
// 
// 	void OpenGLVertexBuffer::Bind() const
// 	{
// 		CN_PROFILE_FUNCTION();
// 
// 		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
// 	}	
// 
// 	void OpenGLVertexBuffer::Unbind() const
// 	{
// 		CN_PROFILE_FUNCTION();
// 
// 		glBindBuffer(GL_ARRAY_BUFFER, 0);
// 	}
// 
// 
// 	// --------------------------------------------------------------------
// 	//							Index Buffer
// 	// --------------------------------------------------------------------
// 
// 	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
// 		: m_Count(count)
// 	{
// 		glCreateBuffers(1, &m_RendererID);
// 		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
// 		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
// 	}
// 
// 	OpenGLIndexBuffer::~OpenGLIndexBuffer()
// 	{
// 		glDeleteBuffers(1, &m_RendererID);
// 	}
// 
// 	void OpenGLIndexBuffer::Bind() const
// 	{
// 		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
// 	}
// 
// 	void OpenGLIndexBuffer::Unbind() const
// 	{
// 		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
// 	}

}