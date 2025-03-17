#pragma once

#include "Crimson/Renderer/Buffer.h"

namespace Crimson {


	// --------------------------------------------------------------------
	//							Vertex Buffer
	// --------------------------------------------------------------------


	class OpenGLVertexBuffer :public VertexBuffer {
	public:

		OpenGLVertexBuffer(const float* data, size_t size);
		OpenGLVertexBuffer(size_t size, BufferStorageType Storage_Type = BufferStorageType::MUTABLE);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetData(size_t size, const void* data) override;
		virtual void* MapBuffer(size_t size) override;
	private:
		unsigned int m_RendererID;
	};

	// 	// --------------------------------------------------------------------
	// 	//							Index Buffer
	// 	// --------------------------------------------------------------------
	class OpenGLIndexBuffer :public IndexBuffer {
	public:

		OpenGLIndexBuffer(const uint32_t* data, size_t size);
		~OpenGLIndexBuffer();

		void Bind() const override;
		void UnBind() const override;

		size_t GetCount() override;

	private:
		size_t m_Elements;
		unsigned int m_RendererID;
	};
}