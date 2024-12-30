#include <Crimson.h>

#include "imgui/imgui.h"

#include "Sandbox2D.h"


class ExampleLayer : public Crimson::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1.6f, true), m_Rotation(0.0f), m_CameraSpeed(2.0f), m_RotationSpeed(45.0f)
	{

		auto& textureShader = m_ShaderLibrary.Load("assets/shaders/texture.shader");

	}
	
	void OnUpdate(Crimson::TimeStep timeStep) override
	{
		
	

	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Crimson::Event& e) override
	{

	}

	bool OnKeyPressedEvent(Crimson::KeyPressedEvent& event)
	{
		return false;
	}

private:

	Crimson::ShaderLibrary m_ShaderLibrary;
	Crimson::OrthographicCameraController m_CameraController;

	crm::vec3 m_Position;
	float m_Rotation;
	float m_CameraSpeed;
	float m_RotationSpeed;

};


class Sandbox : public Crimson::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer);

		//in sandbox2d.cpp
		PushLayer(new Sandbox2D);
	}

	~Sandbox()
	{
	}

};

Crimson::Application* Crimson::CreateApplication()
{
	return new Sandbox;
}