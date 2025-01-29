#pragma once

#include "Crimson/Renderer/Buffer.h"

namespace Crimson {


	// --------------------------------------------------------------------
	//							Vertex Buffer
	// --------------------------------------------------------------------


	class OpenGLVertexBuffer :public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* data, size_t size);
		OpenGLVertexBuffer(size_t size, BufferStorageType Storage_Type = BufferStorageType::MUTABLE);
		~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void SetData(size_t size, const void* data) override;
		virtual void* MapBuffer(size_t size) override;
	private:
		unsigned int m_RendererID;
	};


	class OpenGLIndexBuffer :public IndexBuffer {
	public:
		OpenGLIndexBuffer(unsigned int* data, size_t size);
		~OpenGLIndexBuffer();
		void Bind() const override;
		void UnBind() const override;
		size_t GetCount()override;
	private:
		size_t m_Elements;
		unsigned int m_RendererID;
	};

// 	class OpenGLVertexBuffer : public VertexBuffer
// 	{
// 	public:
// 		OpenGLVertexBuffer(uint32_t size);
// 		OpenGLVertexBuffer(float* vertices, uint32_t size);
// 		virtual ~OpenGLVertexBuffer();
// 
// 		virtual void SetData(const void* data, uint32_t size) override;
// 
// 
// 		virtual void Bind() const override;
// 		virtual void Unbind() const override;
// 
// 		virtual inline void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
// 		virtual inline const BufferLayout& GetLayout() const override { return m_Layout; }
// 
// 	private:
// 		uint32_t m_RendererID;
// 		BufferLayout m_Layout;
// 	};
// 
// 	// --------------------------------------------------------------------
// 	//							Index Buffer
// 	// --------------------------------------------------------------------
// 
// 
// 	class OpenGLIndexBuffer : public IndexBuffer
// 	{
// 	public:
// 		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
// 		virtual ~OpenGLIndexBuffer();
// 
// 		virtual void Bind() const override;
// 		virtual void Unbind() const override;
// 
// 		virtual uint32_t GetCount() const override { return m_Count; }
// 
// 	private:
// 		uint32_t m_RendererID;
// 		uint32_t m_Count;
// 	};

}