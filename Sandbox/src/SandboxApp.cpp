#include <Crimson.h>

#include <Crimson/Core/EntryPoint.h>
#include "Sandbox2dApp.h"
using namespace Crimson;

class Sandbox :public Crimson::Application
{
public:
	Sandbox(){
		//PushLayer(new GameLayer());
		//PushOverlay(new Hazel::ImGuiLayer());
		PushLayer(new SandBox2dApp());
	}
	~Sandbox(){}
};

Crimson::Application* Crimson::CreateApplication() {
	return new Sandbox();
}
