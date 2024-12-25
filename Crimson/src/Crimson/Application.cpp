#include "cnpch.h"
#include "Application.h"
#include "Input.h"

#include "Crimson/Events/ApplicationEvent.h"
#include "Crimson/Events/KeyEvent.h"
#include "Crimson/Events/MouseEvent.h"
#include "Subsystems.h"

// testing chroma math
#include <crm_mth.h>

#include <Glad/glad.h>


namespace Crimson {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		CN_CORE_ASSERT(s_Instance == nullptr, "Already Created Application!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
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
			glClearColor(0, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// we can use range based for loop because we implimented begin and end
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			// testing ... 
			

			//crm::mat4 mat = crm::Translation({ -1.f,-1.f,5.f });
			//mat = crm::Translation(mat,{ 1.f,1.f,1.f });

			// should be 0, 0, 6, 1
			//CN_CORE_INFO("{0},{1},{2},{3}", mat.column_vector[3].x, mat.column_vector[3].y, mat.column_vector[3].z, mat.column_vector[3].w);

			 //should be 1, 0, -1
			// there is some precision 
			//CN_CORE_INFO("{0}, {1}, {2}", mat.column_vector[0].x, mat.column_vector[1].y, mat.column_vector[2].y);

			// glfw key space is keycode 32
			//bool state = Input::IsKeyPressed();
			//CN_CORE_TRACE("{0}", state);

			// glfw mb0 is left
 			//bool mouse = Input::IsMouseButtonPressed(0);
 			//CN_CORE_TRACE("{0}", mouse);

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