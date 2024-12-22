#include <Crimson.h>


class ExampleLayer : public Crimson::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}
	
	void OnUpdate() override
	{
		if (Crimson::Input::IsKeyPressed(CRIMSON_KEY_SPACE))
			CN_TRACE("Space Is Pressed");
		//CN_INFO("ExampleLayer::Update");
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
		PushOverlay(new Crimson::ImGuiLayer());
	}

	~Sandbox()
	{
	}

};

Crimson::Application* Crimson::CreateApplication()
{
	return new Sandbox();
}