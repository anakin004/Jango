#pragma once

#include "cnpch.h"

#include "Crimson/LayerStack.h"
#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

#include "Crimson/ImGui/ImGuiLayer.h"
#include "Crimson/Renderer/Shader.h"
#include "Crimson/Renderer/Buffer.h"
#include "Crimson/Renderer/VertexArray.h"
#include "Crimson/Renderer/RendererAPI.h"
#include "Crimson/Renderer/OrthographicCamera.h"

namespace Crimson {

	/*
	    @brief Application is a singleton, since we will only have one application for the programs lifetime
	    being one Crimson Engine application
	*/
	class CRIMSON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		static inline Application& Get() { return *s_Instance; }

	private:

		bool OnWindowClosed(WindowCloseEvent& e);
	
	private:

		
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;

		// there will now be an explicit imgui layer since its pretty intrinsic to the engine
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		TimeStep m_TimeStep;
		float m_PreviousFrameTime = 0.0f;

	private:
		// only one application -> Crimson Application
		static Application* s_Instance;
	};


	// to be defined in client
	Application* CreateApplication();


}
