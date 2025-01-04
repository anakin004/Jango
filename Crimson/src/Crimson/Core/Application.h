
#pragma once
#include "Core.h"
#include "Window.h"
#include "Crimson/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Crimson/ImGui/ImGuiLayer.h"
#include "Crimson/Renderer/Shader.h"
#include "Crimson/Renderer/Buffer.h"
#include "Crimson/Renderer/OrthographicCamera.h"
#include "KeyCodes.h"
#include "Crimson/Core/TimeStep.h"

namespace Crimson {
	class Application { //set this class as dll export
	public:
		Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* Overlay);

		inline Window& GetWindow() { return *m_window; }

		static inline Application& Get() { return *getApplication; }

		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	public:
		static TimeStep deltaTime;
		glm::vec3 v3;
		float v = 0;
		float r = 0;
	private:
		ImGuiLayer* m_ImGuiLayer;
		std::unique_ptr<Window> m_window;
		bool m_Running = true;
		bool closeWindow(WindowCloseEvent&);
		LayerStack m_layerstack;
		static Application* getApplication;
		Shader* shader;
		float m_LastFrameTime;
	};
	//define in client (not in engine dll)
	Application* CreateApplication();

}

// #pragma once
// 
// #include "cnpch.h"
// 
// #include "Crimson/Core/LayerStack.h"
// #include "Core.h"
// #include "Crimson/Events/Event.h"
// #include "Crimson/Events/ApplicationEvent.h"
// #include "Window.h"
// 
// #include "Crimson/ImGui/ImGuiLayer.h"
// #include "Crimson/Renderer/Shader.h"
// #include "Crimson/Renderer/Buffer.h"
// #include "Crimson/Renderer/VertexArray.h"
// #include "Crimson/Renderer/RendererAPI.h"
// #include "Crimson/Renderer/OrthographicCamera.h"
// 
// namespace Crimson {
// 
// 	/*
// 	    @brief Application is a singleton, since we will only have one application for the programs lifetime
// 	    being one Crimson Engine application
// 	*/
// 	class Application
// 	{
// 	public:
// 		Application();
// 		virtual ~Application();
// 
// 		void Run();
// 
// 		void OnEvent(Event& e);
// 
// 		void PushLayer(Layer* layer);
// 		void PushOverlay(Layer* overlay);
// 
// 		inline Window& GetWindow() { return *m_Window; }
// 		static inline Application& Get() { return *s_Instance; }
// 
// 	private:
// 
// 		bool OnWindowClosed(WindowCloseEvent& e);
// 		bool OnWindowResize(WindowResizeEvent& e);
// 	
// 	private:
// 
// 		
// 		bool m_Running = true;
// 		Scope<Window> m_Window;
// 
// 		// imguilayer is in the application class because its intrinsic to the engine
// 		ImGuiLayer* m_ImGuiLayer;
// 		LayerStack m_LayerStack;
// 
// 		TimeStep m_TimeStep;
// 		float m_PreviousFrameTime = 0.0f;
// 
// 	private:
// 		// only one application -> Crimson Application
// 		static Application* s_Instance;
// 
// 		bool m_Minimized = false;
// 	};
// 
// 
// 	// to be defined in client
// 	Application* CreateApplication();
// 
// 
// }
