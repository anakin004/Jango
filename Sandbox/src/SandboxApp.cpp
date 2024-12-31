#include <Crimson.h>

#include "GameLayer.h"

class Sandbox : public Crimson::Application
{
public:
	Sandbox()
	{
		PushLayer(new GameLayer());
	}

	~Sandbox()
	{
	}
};

Crimson::Application* Crimson::CreateApplication()
{
	return new Sandbox();
}