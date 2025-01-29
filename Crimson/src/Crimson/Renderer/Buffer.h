#pragma once

#include <string>

#

namespace Crimson {




	enum class BufferStorageType : uint8_t {
		MUTABLE, IMMUTABLE
	};

	enum class ShaderDataType : uint8_t
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat2, Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};
	
	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{

		switch (type)
		{
		case ShaderDataType::Float:			return 4;
		case ShaderDataType::Float2:		return 4 * 2;
		case ShaderDataType::Float3:		return 4 * 3;
		case ShaderDataType::Float4:		return 4 * 4;
		case ShaderDataType::Mat2:			return 4 * 2 * 2;
		case ShaderDataType::Mat3:			return 4 * 3 * 3;
		case ShaderDataType::Mat4:			return 4 * 4 * 4;
		case ShaderDataType::Int:			return 4;
		case ShaderDataType::Int2:			return 4 * 2;
		case ShaderDataType::Int3:			return 4 * 3;
		case ShaderDataType::Int4:			return 4 * 4;
		case ShaderDataType::Bool:			return 1;
		}

		CN_CORE_ASSERT(false, "Unknown Shader Data Type!");
		return 0;
	}




	struct BufferElements {

		std::string Name;
		ShaderDataType Type;
		size_t Offset;
		bool Normalized;

		BufferElements(std::string name, ShaderDataType type)
			:Type(type), Name(name), Offset(0), Normalized(false) {
		}
	};




	class BufferLayout {
	public:
		BufferLayout() = default;
		void push(std::string name, ShaderDataType type);

		inline std::vector<BufferElements*> GetElements() { return m_Elements; }
		inline unsigned int GetStride() { return Stride; }

	private:
		unsigned int GetSize(ShaderDataType t);
		std::vector<BufferElements*> m_Elements;
		unsigned int Stride = 0;
	};


	class VertexBuffer {
	public:
		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;
		virtual void SetData(size_t size, const void* data) = 0;
		virtual void* MapBuffer(size_t size) = 0;

		static Ref<VertexBuffer> Create(float* data, size_t size);
		static Ref<VertexBuffer> Create(size_t size, BufferStorageType Storage_Type = BufferStorageType::MUTABLE);
	};


	class IndexBuffer {
	public:
		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;
		virtual size_t GetCount() = 0;
		static Ref<IndexBuffer> Create(uint32_t* data, size_t count);
	};

	class VertexArray {
	public:
		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;
		virtual void AddBuffer(std::shared_ptr<BufferLayout>& layout, std::shared_ptr<VertexBuffer>& vbo) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;
		virtual unsigned int GetVertexArrayID() = 0;
		static Ref<VertexArray> Create();
	};

}