#include "cnpch.h"
#include "WindowsWindow.h"
#include "Crimson/Core.h"
#include "Crimson/Log.h"
#include "Crimson/Events/ApplicationEvent.h"
#include "Crimson/Events/MouseEvent.h"
#include "Crimson/Events/KeyEvent.h"
#include "Crimson/Events/Event.h"

namespace Crimson {
	
	static bool s_GLFWBooted = false;

	Window* Window::Create(const WindowAttribs& attribs)
	{
		return new WindowsWindow(attribs);
	}

	WindowsWindow::WindowsWindow(const WindowAttribs& attribs)
	{
		Init(attribs);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowAttribs& attribs)
	{
		m_Data.Title = attribs.Title;
		m_Data.Width = attribs.Width;
		m_Data.Height = attribs.Height;

		CN_CORE_INFO("Creating Window {0} ({1}, {2})", attribs.Title, attribs.Width, attribs.Height);

		if (s_GLFWBooted == false)
		{
			// need to terminate glfw, but not when we destruct window
			// we may have multiple windows
			int success = glfwInit();
			CN_CORE_ASSERT(success, "GLFW Failed To Initalized!");

			s_GLFWBooted = true;
		}

		
		m_Window = glfwCreateWindow((int)attribs.Width, (int)attribs.Height, m_Data.Title.c_str(), nullptr, nullptr);
		
		if (m_Window == NULL) 
		{ 
			CN_CORE_ASSERT(false, "Failed to Create Window") 
		}
		

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		//vsync true default 
		SetVSync(true);


		//glfw callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);

			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)    
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}
}
