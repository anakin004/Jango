#include <Crimson.h>

#include "Sandbox2D.h"

class Sandbox : public Crimson::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Crimson::Application* Crimson::CreateApplication()
{
	return new Sandbox();
}