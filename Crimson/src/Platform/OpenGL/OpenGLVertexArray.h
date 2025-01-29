#pragma once

#include "Crimson/Renderer/Buffer.h"

namespace Crimson {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		void Bind()const override;
		void UnBind()const override;
		void AddBuffer(Ref<BufferLayout>& layout, Ref<VertexBuffer>& vbo) override;
		void SetIndexBuffer(Ref<IndexBuffer> IndexBuffer) override;

		const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() override { return m_VertexBuffer; }
		unsigned int GetVertexArrayID() override { return m_Renderer; }
	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
		unsigned int m_Renderer;
	};


}