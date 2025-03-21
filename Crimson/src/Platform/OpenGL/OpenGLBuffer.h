#pragma once

#include "Crimson/Renderer/Buffer.h"

namespace Crimson {


	// --------------------------------------------------------------------
	//							Vertex Buffer
	// --------------------------------------------------------------------


	class OpenGLVertexBuffer :public VertexBuffer {
	public:

		OpenGLVertexBuffer(const float* data, uint32_t size);
		OpenGLVertexBuffer(uint32_t size, BufferStorageType Storage_Type = BufferStorageType::MUTABLE);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetData(uint32_t size, const void* data) override;
		virtual void* MapBuffer(uint32_t size) override;
	private:
		unsigned int m_RendererID;
	};

	// 	// --------------------------------------------------------------------
	// 	//							Index Buffer
	// 	// --------------------------------------------------------------------
	class OpenGLIndexBuffer :public IndexBuffer {
	public:

		OpenGLIndexBuffer(const uint32_t* data, uint32_t size);
		~OpenGLIndexBuffer();

		void Bind() const override;
		void UnBind() const override;

		inline uint32_t GetCount() override { return m_Elements; }

	private:
		uint32_t m_Elements;
		unsigned int m_RendererID;
	};
}