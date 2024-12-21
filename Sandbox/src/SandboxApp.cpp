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
		CN_INFO("ExampleLayer::Update");
	}

	void OnEvent(Crimson::Event& event) override
	{
		CN_INFO("{0}", event.ToString());
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