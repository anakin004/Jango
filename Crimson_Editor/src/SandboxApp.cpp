
#include <Crimson.h>
#include "Crimson/Core/EntryPoint.h"
#include "CrimsonEditor.h"


class Sandbox :public Crimson::Application
{
public:
	Sandbox(){
		//PushLayer(new GameLayer());
		//PushOverlay(new Hazel::ImGuiLayer());
		PushLayer(new CrimsonEditor());
	}
	~Sandbox(){}
};

Crimson::Application* Crimson::CreateApplication() {
	return new Sandbox();
}
