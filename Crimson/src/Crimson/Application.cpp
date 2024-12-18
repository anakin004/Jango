#include "cnpch.h"
#include "Application.h"
#include "Crimson/Events/ApplicationEvent.h"
#include "Crimson/Events/KeyEvent.h"
#include "Crimson/Events/MouseEvent.h"
#include "Crimson/Log.h"

namespace Crimson {


	Application::~Application()
	{
	} 

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		KeyReleasedEvent k(1);

		if (e.IsInCategory(EventCategoryApplication)) {
			CN_TRACE(e.ToString());
		}
		if (e.IsInCategory(EventCategoryInput)) {
			CN_TRACE(k.ToString());
		}

		while (true) {

		}
	}

	Application::Application()
	{
	}

}