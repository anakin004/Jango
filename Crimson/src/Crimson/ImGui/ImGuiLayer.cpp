#include "cnpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiGLRenderer.h"
#include "Platform/OpenGL/ImGuiGLFW.h"
#include "Crimson/Application.h"


// temp
#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace Crimson {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnUpdate()
	{

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		Window& window = app.GetWindow();
		io.DisplaySize = ImVec2(window.GetWidth(), window.GetHeight());
	

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.f / 60.f);
		m_Time = time;


		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(CN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(CN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(CN_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(CN_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(CN_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(CN_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(CN_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(CN_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		// to let other layers potentially handle this
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();            // not held down
		io.AddMouseButtonEvent(e.GetMouseButton(), false );
		//io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetX(), e.GetY());
		//io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		// the scancode not used, we dont need it so set to 0
		// refer to ImGuiGLFW.h for more info
		ImGuiKey imguiKey = ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode(), 0);
		
		// dont know if i need these
		
// 		io.KeyCtrl = ImGui::IsKeyPressed(ImGuiKey_LeftCtrl) || ImGui::IsKeyPressed(ImGuiKey_RightCtrl);
// 		io.KeyShift = ImGui::IsKeyPressed(ImGuiKey_LeftShift) || ImGui::IsKeyPressed(ImGuiKey_RightShift);
// 		io.KeyAlt = ImGui::IsKeyPressed(ImGuiKey_LeftAlt) || ImGui::IsKeyPressed(ImGuiKey_RightAlt);
// 		io.KeySuper = ImGui::IsKeyPressed(ImGuiKey_LeftSuper) || ImGui::IsKeyPressed(ImGuiKey_RightSuper);


		// also check for event key press
 		io.AddKeyEvent(imguiKey, true);


		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey imguiKey = ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode(), 0);


		io.AddKeyEvent(imguiKey, false);
		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(static_cast<unsigned int>(e.GetKeyCode()));

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		// setting io flags 

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		
		ImGui_ImplOpenGL3_Init("#version 410");


	}

	void ImGuiLayer::OnDetach()
	{

	}

}