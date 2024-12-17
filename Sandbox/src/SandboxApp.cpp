#include <Crimson.h>


class Sandbox : public Crimson::Application
{
public:
	Sandbox() 
	{

	}

	~Sandbox() 
	{

	}
};


Crimson::Application* Crimson::CreateApplication()
{
	return new Sandbox();
}