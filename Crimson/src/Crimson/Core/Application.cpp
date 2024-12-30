#include "cnpch.h"
#include "Application.h"
#include "Input.h"

#include "Crimson/Events/ApplicationEvent.h"
#include "Crimson/Events/KeyEvent.h"
#include "Crimson/Events/MouseEvent.h"
#include "Subsystems.h"

#include "Crimson/Renderer/Renderer.h"

#include "Crimson/Core/TimeStep.h"

#include "Crimson/Renderer/OrthographicCamera.h"

#include <GLFW/glfw3.h>

namespace Crimson {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;



	Application::Application()
	{
		CN_PROFILE_FUNCTION()

		CN_CORE_ASSERT(s_Instance == nullptr, "Already Created Application!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();


		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application()
	{
		CN_PROFILE_FUNCTION()
		m_Window.reset();
		Renderer::Shutdown();
		Subsystems::ShutDownGL();

	} 

	void Application::Run()
	{
		CN_PROFILE_FUNCTION()


		while (m_Running) {

			float time = (float)glfwGetTime(); // platform::gettime()
			m_TimeStep = time - m_PreviousFrameTime;
			m_PreviousFrameTime = time;

			if (!m_Minimized)
			{

				{
					CN_PROFILE_SCOPE("Layer OnUpdates")


					// we can use range based for loop because we implimented begin and end
					for (const auto& layer : m_LayerStack)
					{
						layer->OnUpdate(m_TimeStep);
					}

				}


				m_ImGuiLayer->Begin();
				{
					CN_PROFILE_SCOPE("LayerStack OnImGuiRender")

					for (const auto& layer : m_LayerStack)
					{
						layer->OnImGuiRender();
					}
				}
				m_ImGuiLayer->End();

				
			}

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{

		CN_PROFILE_FUNCTION()

		EventDispatcher dispatcher(e);

		// even though we dispatch starting from top layer, on windows closed we dont check other layers
		// we simply terminate
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		
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
		CN_PROFILE_FUNCTION()

		layer->OnAttach();
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		CN_PROFILE_FUNCTION()

		overlay->OnAttach();
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		CN_PROFILE_FUNCTION()

		if (e.GetWidth() == 0 || e.GetHeight() == 0){
			m_Minimized = true;
			return false;
		}

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		m_Minimized = false;
		return false;
	}

}