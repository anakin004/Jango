#include "cnpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "Crimson/Renderer/RenderCommand.h"


namespace Crimson {

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> ColorShader;
		Ref<Shader> TextureShader;
	};

	static Renderer2DStorage* s_Storage = nullptr;

	void Renderer2D::Init()
	{
		s_Storage = new Renderer2DStorage();

		s_Storage->QuadVertexArray = VertexArray::Create();


		float vertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		
		Ref<VertexBuffer> squareBuffer;
		squareBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoords"}
		};

		squareBuffer->SetLayout(layout);

		s_Storage->QuadVertexArray->AddVertexBuffer(squareBuffer);

		uint32_t indices[6] = {
			0,1,2,
			0,3,2
		};

		Ref<IndexBuffer> indexBuffer;
		indexBuffer = IndexBuffer::Create(indices, 6);
		s_Storage->QuadVertexArray->SetIndexBuffer(indexBuffer);


		s_Storage->ColorShader = Shader::Create("assets/shaders/color.shader");
		s_Storage->TextureShader = Shader::Create("assets/shaders/texture.shader");
		s_Storage->TextureShader->Bind();
		s_Storage->TextureShader->SetInt("u_Texture",0);


	}

	void Renderer2D::Shutdown()
	{
		delete s_Storage;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Storage->ColorShader->Bind();
		s_Storage->ColorShader->SetMat4("u_ViewProjection",camera.GetViewProjectionMatrix());

		s_Storage->TextureShader->Bind();
		s_Storage->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const crm::vec2& position, const crm::vec2& size, const crm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);

	}

	void Renderer2D::DrawQuad(const crm::vec3& position, const crm::vec2& size, const crm::vec4& color)
	{
		s_Storage->ColorShader->Bind();
		s_Storage->ColorShader->SetFloat4("u_Color", color);

		crm::mat4 transform = crm::Mul(crm::Translation(crm::mat4(1.0f), position),
									   crm::Scale(crm::mat4(1.0f), { size.x,size.y,1.0f })
									  );

		s_Storage->ColorShader->SetMat4("u_Transform", transform);
		s_Storage->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Storage->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const crm::vec2& position, const crm::vec2& size, const Ref<Texture2D> texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const crm::vec3& position, const crm::vec2& size, const Ref<Texture2D> texture)
	{

		crm::mat4 transform = crm::Mul(crm::Translation(crm::mat4(1.0f), position),
			crm::Scale(crm::mat4(1.0f), { size.x,size.y,1.0f })
		);

		s_Storage->TextureShader->Bind();
		texture->Bind();
		s_Storage->TextureShader->SetMat4("u_Transform", transform);
		s_Storage->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Storage->QuadVertexArray);
	}
	

}