#include "cnpch.h"
#include "OpenGlVertexArray.h"
#include "glad/glad.h"

namespace Crimson {

	unsigned int GetSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:  return 1;
		case ShaderDataType::Float2: return  2;
		case ShaderDataType::Float3: return  3;
		case ShaderDataType::Float4: return  4;
		case ShaderDataType::Int:    return 1;
		case ShaderDataType::Int2:   return  2;
		case ShaderDataType::Int3:   return  3;
		case ShaderDataType::Int4:   return  4;
		case ShaderDataType::Mat2:   return 2 * 2;
		case ShaderDataType::Mat3:   return 3 * 3;
		case ShaderDataType::Mat4:   return 4 * 4;
		default:
			CN_CORE_ERROR("Unidentfied Type")
		}
	}

	GLenum GetType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:  return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Int:    return GL_INT;
		case ShaderDataType::Int2:   return GL_INT;
		case ShaderDataType::Int3:   return GL_INT;
		case ShaderDataType::Int4:   return GL_INT;
		case ShaderDataType::Mat2:   return GL_FLOAT;
		case ShaderDataType::Mat3:   return GL_FLOAT;
		case ShaderDataType::Mat4:   return GL_FLOAT;
		default:
			CN_CORE_ERROR("Unidentfied Type")
		}
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_Renderer);
		glBindVertexArray(m_Renderer);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_Renderer);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_Renderer);
	}
	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddBuffer(std::shared_ptr<BufferLayout>& layout, std::shared_ptr<VertexBuffer>& vbo)
	{
		vbo->Bind();
		Bind();
		auto element = layout->GetElements();
		int size = element.size();
		int offset = 0;
		for (unsigned int i = 0; i < size; i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, GetSize(element[i]->Type), GetType(element[i]->Type), element[i]->Normalized, layout->GetStride(), (const void*)offset);
			offset += GetSize(element[i]->Type) * sizeof(GetType(element[i]->Type));
		}

		m_VertexBuffer.push_back(vbo);
	}
	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> IndexBuffer)
	{
		Bind();
		IndexBuffer->Bind();
		m_IndexBuffer = IndexBuffer;
	}
}

// #include "cnpch.h"
// 
// #include "OpenGLVertexArray.h"
// 
// #include "Crimson/Core/Log.h"
// 
// #include <Glad/glad.h>
// 
// namespace Crimson {
// 
// 	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
// 	{
// 		switch (type)
// 		{
// 		case ShaderDataType::Float:			return GL_FLOAT;
// 		case ShaderDataType::Float2:		return GL_FLOAT;
// 		case ShaderDataType::Float3:		return GL_FLOAT;
// 		case ShaderDataType::Float4:		return GL_FLOAT;
// 		case ShaderDataType::Mat3:			return GL_FLOAT;
// 		case ShaderDataType::Mat4:			return GL_FLOAT;
// 		case ShaderDataType::Int:			return GL_INT;
// 		case ShaderDataType::Int2:			return GL_INT;
// 		case ShaderDataType::Int3:			return GL_INT;
// 		case ShaderDataType::Int4:			return GL_INT;
// 		case ShaderDataType::Bool:			return GL_BOOL;
// 		}
// 
// 		CN_CORE_ASSERT(false, "Unknown Shader Data Type!");
// 		return 0;
// 	}
// 
// 
// 	OpenGLVertexArray::OpenGLVertexArray()
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		glCreateVertexArrays(1, &m_RendererID);
// 		glBindVertexArray(m_RendererID);
// 	}
// 
// 	OpenGLVertexArray::~OpenGLVertexArray()
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		glDeleteVertexArrays(1, &m_RendererID);
// 	}
// 
// 
// 	void OpenGLVertexArray::Bind() const
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		glBindVertexArray(m_RendererID);
// 	}
// 
// 	void OpenGLVertexArray::Unbind() const
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		glBindVertexArray(0);
// 	}
// 
// 	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
// 	{
// 
// 		CN_PROFILE_FUNCTION()
// 
// 		glBindVertexArray(m_RendererID);
// 		vertexBuffer->Bind();
// 
// 		CN_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "No elements in the vertex buffer!");
// 
// 		uint32_t idx = 0;
// 		const auto& layout = vertexBuffer->GetLayout();
// 		
// 		for (const auto& element : layout)
// 		{
// 			glEnableVertexAttribArray(idx);
// 			glVertexAttribPointer(idx,
// 				element.GetComponentCount(),
// 				ShaderDataTypeToOpenGLBaseType(element.Type),
// 				element.Normalized ? GL_TRUE : GL_FALSE,
// 				layout.GetStride(),
// 				(const void*)((uint64_t)(element.Offset)));
// 			idx++;
// 		}
// 
// 
// 		m_VertexBuffers.push_back(vertexBuffer);
// 	}
// 
// 	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
// 	{
// 
// 		CN_PROFILE_FUNCTION()
// 
// 		glBindVertexArray(m_RendererID);
// 		indexBuffer->Bind();
// 
// 		m_IndexBuffer = indexBuffer;
// 	}
// 
// }