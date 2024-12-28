#include <Crimson.h>

#include "Crimson/Core.h"

#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"


class ExampleLayer : public Crimson::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, 0.9f, -0.9f), m_Rotation(0.0f), m_CameraSpeed(2.0f), m_RotationSpeed(45.0f)
	{


		m_VertexArray = Crimson::VertexArray::Create();
		{

			float vertices[7 * 3] = {
				-0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 0.3f, 1.0f,
				0.5f,  -0.5f, 0.0f, 0.5f, 0.7f, 0.3f, 1.0f,
				0.0f,   0.5f, 0.0f, 0.3f, 0.5f, 0.9f, 1.0f,

			};


			m_VertexBuffer = Crimson::VertexBuffer::Create(vertices, sizeof(vertices));


			Crimson::BufferLayout layout = {
				{Crimson::ShaderDataType::Float3, "a_Position"},
				{Crimson::ShaderDataType::Float4, "a_Color" }
			};


			m_VertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(m_VertexBuffer);


			uint32_t indices[3] = {
				0,1,2
			};

			m_IndexBuffer = Crimson::IndexBuffer::Create(indices, 3);
			m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		}

		m_Shader = Crimson::Shader::Create("assets/shaders/testing.shader");

		m_VertexArray->Unbind();


		m_SquareVA = Crimson::VertexArray::Create();

		{
			float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom-left
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // bottom-right
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // top-right
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // top-left
			};
			Crimson::Ref<Crimson::VertexBuffer> squareBuffer;
			squareBuffer = Crimson::VertexBuffer::Create(vertices, sizeof(vertices));

			Crimson::BufferLayout layout = {
				{Crimson::ShaderDataType::Float3, "a_Position"},
				{Crimson::ShaderDataType::Float2, "a_TexCoord" }
			};

			squareBuffer->SetLayout(layout);

			m_SquareVA->AddVertexBuffer(squareBuffer);

			uint32_t indices[6] = {
				0,1,2,
				0,3,2
			};

			Crimson::Ref<Crimson::IndexBuffer> indexBuffer;
			indexBuffer=Crimson::IndexBuffer::Create(indices, 6);
			m_SquareVA->SetIndexBuffer(indexBuffer);


			m_TextureShader=Crimson::Shader::Create("assets/shaders/texture.shader");


			m_Texture = Crimson::Texture2D::Create("assets/textures/linux.png");
			m_Texture->Bind(0);
			std::dynamic_pointer_cast<Crimson::OpenGLShader>(m_TextureShader)->Bind();
			std::dynamic_pointer_cast<Crimson::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

		}
	}
	
	void OnUpdate(Crimson::TimeStep timeStep) override
	{

		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_W))
			m_Position.y += m_CameraSpeed * timeStep;
		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_A))
			m_Position.x -= m_CameraSpeed * timeStep;
		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_S))
			m_Position.y -= m_CameraSpeed * timeStep;
		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_D))
			m_Position.x += m_CameraSpeed * timeStep;
		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_V))
			m_Rotation += m_RotationSpeed * timeStep;
		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_B))
			m_Rotation -= m_RotationSpeed * timeStep;

		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_T))
			m_SquarePosition.y += m_CameraSpeed * timeStep;
		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_F))
			m_SquarePosition.x -= m_CameraSpeed * timeStep;
		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_G))
			m_SquarePosition.y -= m_CameraSpeed * timeStep;
		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_H))
			m_SquarePosition.x += m_CameraSpeed * timeStep;
// 		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_N))
// 			m_Rotation += m_RotationSpeed * timeStep;
// 		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_M))
// 			m_Rotation -= m_RotationSpeed * timeStep;
		

		m_Camera.SetPosition(m_Position);
		m_Camera.SetRotation(m_Rotation);

		// translation defaults to transform a identity matrix if only a vec3 is input
		crm::mat4 transformMat = crm::Translation(m_SquarePosition);

		Crimson::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		Crimson::RenderCommand::Clear();

		Crimson::Renderer::BeginScene(m_Camera);
		
		crm::mat4 scale = crm::Scale(transformMat, crm::vec3(0.05f, 0.05f, 0.05f));

		std::dynamic_pointer_cast<Crimson::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Crimson::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_Red);


		for( int y = 0 ; y < 20 ; y++){
			for (int x = 0; x < 20; x++) {
				crm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				crm::mat4 tMat = crm::Mul(crm::Translation(pos), scale);
				Crimson::Renderer::Submit(m_Shader, m_SquareVA, tMat);
			}
		}

		Crimson::Renderer::Submit(m_TextureShader, m_SquareVA, crm::Scale(transformMat, crm::vec3(1.5f, 1.5f, 1.5f)));

		
		//Crimson::Renderer::Submit(m_Shader, m_VertexArray);
		Crimson::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Color", m_Red.data);

		ImGui::End();
	}

	void OnEvent(Crimson::Event& event) override
	{
		Crimson::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Crimson::KeyPressedEvent>(CN_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Crimson::KeyPressedEvent& event)
	{
		return false;
	}

private:

	Crimson::Ref<Crimson::Shader> m_Shader;
	Crimson::Ref<Crimson::Shader> m_TextureShader;
	Crimson::Ref<Crimson::Texture2D> m_Texture;

	Crimson::Ref<Crimson::VertexArray> m_VertexArray;

	Crimson::Ref<Crimson::VertexBuffer> m_VertexBuffer;
	Crimson::Ref<Crimson::IndexBuffer> m_IndexBuffer;

	Crimson::Ref<Crimson::VertexArray> m_SquareVA;

	Crimson::OrthographicCamera m_Camera;

	crm::vec3 m_Position;
	float m_Rotation;
	float m_CameraSpeed;
	float m_RotationSpeed;

	crm::vec3 m_SquarePosition;


	crm::vec4 m_Red = { 0.8f, 0.2f, 0.3f, 1.0f };
	crm::vec4 m_Blue = { 0.2f, 0.3f, 0.8f, 1.0f };
};


class Sandbox : public Crimson::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
	}

	~Sandbox()
	{
	}

};

Crimson::Application* Crimson::CreateApplication()
{
	return  new Sandbox;
}