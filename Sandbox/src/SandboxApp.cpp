#include <Crimson.h>

#include "imgui/imgui.h"

class ExampleLayer : public Crimson::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}
	
	void OnUpdate() override
	{
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello!");
		ImGui::End();
	}

	void OnEvent(Crimson::Event& event) override
	{
	}
};


class Sandbox : public Crimson::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
	}

	~Sandbox()
	{
	}

};

Crimson::Application* Crimson::CreateApplication()
{
	return new Sandbox();
}