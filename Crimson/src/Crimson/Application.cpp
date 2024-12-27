#include "cnpch.h"
#include "Application.h"
#include "Input.h"

#include "Crimson/Events/ApplicationEvent.h"
#include "Crimson/Events/KeyEvent.h"
#include "Crimson/Events/MouseEvent.h"
#include "Subsystems.h"

#include "Crimson/Renderer/RenderCommand.h"
#include "Crimson/Renderer/Renderer.h"


#include "Crimson/Renderer/OrthographicCamera.h"

#include <crm_mth.h>

#include <glad/glad.h>

namespace Crimson {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;



	Application::Application()
		  //        l,     r,    t,     b
		: m_Camera(-1.6f, 1.6f, 0.9f, -0.9f)
	{
		CN_CORE_ASSERT(s_Instance == nullptr, "Already Created Application!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		{

			float vertices[7 * 3] = {
				-0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 0.3f, 1.0f,
				0.5f,  -0.5f, 0.0f, 0.5f, 0.7f, 0.3f, 1.0f,
				0.0f,   0.5f, 0.0f, 0.3f, 0.5f, 0.9f, 1.0f,

			};

			m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));


			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color" }
			};

			m_VertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(m_VertexBuffer);


			uint32_t indices[3] = {
				0,1,2
			};

			m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
			m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		}

		m_Shader.reset(Shader::Create("src/testing.shader"));
		m_Shader->Bind();


		m_VertexArray->Unbind();


		m_SquareVA.reset(VertexArray::Create());

		{
			float vertices[7 * 4] = {
				-0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 0.4f, 1.0f,
				0.5f,  -0.5f, 0.0f, 0.5f, 0.2f, 0.6f, 1.0f,
				-0.5f,  0.5f, 0.0f, 0.3f, 0.5f, 0.1f, 1.0f,
				 0.5f,  0.5f, 0.0f, 0.3f, 0.5f, 0.1f, 1.0f,

			};
			std::shared_ptr<VertexBuffer> squareBuffer;
			squareBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
			
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color" }
			};

			squareBuffer->SetLayout(layout);

			m_SquareVA->AddVertexBuffer(squareBuffer);

			uint32_t indices[6] = {
				0,1,2,
				2,1,3
			};

			std::shared_ptr<IndexBuffer> indexBuffer;
			indexBuffer.reset(IndexBuffer::Create(indices, 6));
			m_SquareVA->SetIndexBuffer(indexBuffer);
		}

	}

	Application::~Application()
	{

		// dont really like this, will probably do a cleanup function outside of app to shutdown gl
		// and others if needed
		// we call reset on the unique pointer so its released before we call shutdowngl
		// and we arent shutting down opengl before freeing window

		m_Window.reset();
		Subsystems::ShutDownGL();
	} 

	void Application::Run()
	{
		while (m_Running) {

			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
			RenderCommand::Clear();

			Renderer::BeginScene(m_Camera);
			Renderer::Submit(m_Shader, m_SquareVA);
			Renderer::Submit(m_Shader, m_VertexArray);
			Renderer::EndScene();
			
			// we can use range based for loop because we implimented begin and end
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		// even though we dispatch starting from top layer, on windows closed we dont check other layers
		// we simply terminate
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		
		//CN_CORE_TRACE(e.ToString());

		// going backwards since if an overlay with some button handles event
		// we are done, we dont propogate
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			// we need to decrement first since it points one past pos
			(*(--it))->OnEvent(e);
			if (e.GetHandled())
				break;
		}


	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}