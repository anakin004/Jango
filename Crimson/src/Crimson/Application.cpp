#include "cnpch.h"
#include "Application.h"
#include "Input.h"

#include "Crimson/Events/ApplicationEvent.h"
#include "Crimson/Events/KeyEvent.h"
#include "Crimson/Events/MouseEvent.h"
#include "Subsystems.h"


#include <Glad/glad.h>
#include <crm_mth.h>


namespace Crimson {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;


	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type) 
		{
		case ShaderDataType::Float:			return GL_FLOAT;
		case ShaderDataType::Float2:		return GL_FLOAT;
		case ShaderDataType::Float3:		return GL_FLOAT;
		case ShaderDataType::Float4:		return GL_FLOAT;
		case ShaderDataType::Mat3:			return GL_FLOAT;
		case ShaderDataType::Mat4:			return GL_FLOAT;
		case ShaderDataType::Int:			return GL_INT;
		case ShaderDataType::Int2:			return GL_INT;
		case ShaderDataType::Int3:			return GL_INT;
		case ShaderDataType::Int4:			return GL_INT;
		case ShaderDataType::Bool:			return GL_BOOL;
		}

		CN_CORE_ASSERT(false, "Unknown Shader Data Type!");
		return 0;
	}

	Application::Application()
	{
		CN_CORE_ASSERT(s_Instance == nullptr, "Already Created Application!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[7*3] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 0.3f, 1.0f,  
			0.5f,  -0.5f, 0.0f, 0.5f, 0.7f, 0.3f, 1.0f,   
			0.0f,   0.5f, 0.0f, 0.3f, 0.5f, 0.9f, 1.0f, 

		}; 

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));


 		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color" }
		};

		int idx = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(idx);
			glVertexAttribPointer(idx, 
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)((uint64_t)(element.Offset)));
			CN_CORE_INFO("{0}, {1}, {2}, {3}, {4}, {5}", idx, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized, layout.GetStride(), element.Offset);
			idx++;
		}




		m_VertexBuffer->SetLayout(layout);

		uint32_t indices[3] = {
			0,1,2
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
		m_Shader.reset(Shader::Create("src/testing.shader"));
		m_Shader->Bind();


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
			glClearColor(0.1f, 0.1f, 0.1f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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