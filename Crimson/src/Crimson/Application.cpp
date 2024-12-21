#include "cnpch.h"
#include "Application.h"

#include "Crimson/Events/ApplicationEvent.h"
#include "Crimson/Events/KeyEvent.h"
#include "Crimson/Events/MouseEvent.h"

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

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch < WindowCloseEvent >(BIND_EVENT_FN(OnWindowClosed));
		
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