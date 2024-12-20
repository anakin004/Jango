#pragma once

#include "cnpch.h"

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Crimson {

	/*
	    @brief will be a singleton, since we will only have one application for the programs lifetime
	    being one Crimson Engine application
	*/
	class CRIMSON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
	};


	// to be defined in client
	Application* CreateApplication();


}
