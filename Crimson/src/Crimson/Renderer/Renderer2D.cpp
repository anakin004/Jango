#include "cnpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "Crimson/Renderer/RenderCommand.h"


namespace Crimson {

	struct QuadVertex
	{
		crm::vec3 Position;
		crm::vec4 Color;
		crm::vec2 TexCoord;
		// add texid
	};


	struct Renderer2DData
	{
		const uint32_t maxQuads = 10000;
		const uint32_t maxVerts = maxQuads * 4;
		const uint32_t maxIndices = maxQuads * 6;
		
		uint32_t QuadIndexCount = 0;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

	};


	static Renderer2DData s_Storage;

	void Renderer2D::Init()
	{


		CN_PROFILE_FUNCTION();

		s_Storage.QuadVertexArray = VertexArray::Create();



		s_Storage.QuadVertexBuffer = VertexBuffer::Create(s_Storage.maxVerts * sizeof(QuadVertex));

		BufferLayout layout(
			{
			{ShaderDataType::Float3, "a_Position", offsetof(QuadVertex, Position)},
			{ShaderDataType::Float4, "a_Color", offsetof(QuadVertex, Color)},
			{ShaderDataType::Float2, "a_TexCoords", offsetof(QuadVertex, TexCoord)},
			},

			sizeof(QuadVertex)
		);

		s_Storage.QuadVertexBuffer->SetLayout(layout);
		s_Storage.QuadVertexArray->AddVertexBuffer(s_Storage.QuadVertexBuffer);


		s_Storage.QuadVertexBufferBase = new QuadVertex[s_Storage.maxVerts];


		uint32_t* quadIndices = new uint32_t[s_Storage.maxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Storage.maxIndices; i+=6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Storage.maxIndices);
		s_Storage.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_Storage.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Storage.WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

		s_Storage.TextureShader = Shader::Create("assets/shaders/texture.shader");
		s_Storage.TextureShader->Bind();
		//s_Storage.TextureShader->SetInt("u_Texture",0);

	}

	void Renderer2D::Shutdown()
	{
		delete[] s_Storage.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		CN_PROFILE_FUNCTION();


		s_Storage.TextureShader->Bind();
		s_Storage.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());


		s_Storage.QuadVertexBufferPtr = s_Storage.QuadVertexBufferBase;

		s_Storage.QuadIndexCount = 0;

	}

	void Renderer2D::EndScene()
	{

		CN_PROFILE_FUNCTION();

		// get memory in bytes
		uint32_t dataSize = (uint8_t*)s_Storage.QuadVertexBufferPtr - (uint8_t*)s_Storage.QuadVertexBufferBase;
		s_Storage.QuadVertexBuffer->SetData(s_Storage.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawIndexed(s_Storage.QuadVertexArray, s_Storage.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const crm::vec2& position, const crm::vec2& size, const crm::vec4& color)
	{
		DrawQuad(crm::vec3{ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const crm::vec3& position, const crm::vec2& size, const crm::vec4& color)
	{
		CN_PROFILE_FUNCTION();
		
		s_Storage.QuadVertexBufferPtr->Position = position;
		s_Storage.QuadVertexBufferPtr->Color = color;
		s_Storage.QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
		s_Storage.QuadVertexBufferPtr++;

		s_Storage.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		s_Storage.QuadVertexBufferPtr->Color = color;
		s_Storage.QuadVertexBufferPtr->TexCoord = {1.0f, 0.0f};
		s_Storage.QuadVertexBufferPtr++;

		s_Storage.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		s_Storage.QuadVertexBufferPtr->Color = color;
		s_Storage.QuadVertexBufferPtr->TexCoord = {1.0f, 1.0f};
		s_Storage.QuadVertexBufferPtr++;

		s_Storage.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		s_Storage.QuadVertexBufferPtr->Color = color;
		s_Storage.QuadVertexBufferPtr->TexCoord = {0.0f, 1.0f};
		s_Storage.QuadVertexBufferPtr++;

		s_Storage.QuadIndexCount += 6;

// 		s_Storage.WhiteTexture->Bind();
// 		s_Storage.TextureShader->SetFloat4("u_Color", color);
// 
// 
// 		crm::mat4 transform = crm::Mul(crm::Translation(crm::mat4(1.0f), position),
// 			(crm::Scale(crm::mat4(1.0f), crm::vec3{ size.x,size.y,1.0f })
// 		));
// 
// 		s_Storage.TextureShader->SetMat4("u_Transform", transform);
// 		s_Storage.QuadVertexArray->Bind();
// 		RenderCommand::DrawIndexed(s_Storage.QuadVertexArray);
	}


	void Renderer2D::DrawQuad(const crm::vec2& position, const crm::vec2& size, float rotation, const crm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, color);

	}

	void Renderer2D::DrawQuad(const crm::vec3& position, const crm::vec2& size, float rotation, const crm::vec4& color)
	{
		CN_PROFILE_FUNCTION();


		s_Storage.WhiteTexture->Bind();
		s_Storage.TextureShader->SetFloat4("u_Color", color);


		crm::mat4 transform = crm::Mul(crm::Translation(crm::mat4(1.0f), position),
			(crm::Scale(crm::mat4(1.0f), crm::vec3{ size.x,size.y,1.0f })
				));

		s_Storage.TextureShader->SetMat4("u_Transform", transform);
		s_Storage.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Storage.QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const crm::vec2& position, const crm::vec2& size, const Ref<Texture2D> texture)
	{
		DrawQuad(crm::vec3{ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const crm::vec3& position, const crm::vec2& size, const Ref<Texture2D> texture)
	{

		CN_PROFILE_FUNCTION();

		s_Storage.TextureShader->SetFloat4("u_Color", { 1.0f,1.0f,1.0f,1.0f });


		texture->Bind();

		crm::mat4 transform = crm::Mul(crm::Translation(crm::mat4(1.0f), position),
			crm::Scale(crm::mat4(1.0f), crm::vec3{ size.x, size.y, 1.0f }));


		s_Storage.TextureShader->SetMat4("u_Transform", transform);


		s_Storage.TextureShader->SetMat4("u_Transform", transform);
		s_Storage.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Storage.QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const crm::vec2& position, const crm::vec2& size, float rotation, const Ref<Texture2D> texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture);
	}

	void Renderer2D::DrawQuad(const crm::vec3& position, const crm::vec2& size, float rotation, const Ref<Texture2D> texture)
	{

		CN_PROFILE_FUNCTION();
			
		s_Storage.TextureShader->SetFloat4("u_Color", { 1.0f,1.0f,1.0f,1.0f });


		texture->Bind();

 		crm::mat4 transform = crm::Mul(crm::Translation(crm::mat4(1.0f), position)
 			, crm::Mul(crm::ZRotation(rotation)
 				, crm::Scale(crm::mat4(1.0f), crm::vec3{ size.x, size.y, 1.0f })));


		s_Storage.TextureShader->SetMat4("u_Transform", transform);


		s_Storage.TextureShader->SetMat4("u_Transform", transform);
		s_Storage.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Storage.QuadVertexArray);
	}


}