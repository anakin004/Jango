#include "cnpch.h"
#include "Application.h"

#include "Crimson/Events/ApplicationEvent.h"
#include "Crimson/Events/KeyEvent.h"
#include "Crimson/Events/MouseEvent.h"

#include <GLFW/glfw3.h>

namespace Crimson {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	} 

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		KeyReleasedEvent k(1);

		CN_CORE_CRITICAL("HELLLOOO CRIMSON ENGINE !!>><<!!!!");

		while (m_Running) {
			glClearColor(0, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}