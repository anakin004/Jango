#pragma once

#include "Core.h"
#include "Application.h"

#ifdef CN_PLATFORM_WINDOWS

extern Crimson::Application* Crimson::CreateApplication();


// allows us to define our entry pointer seperate from application, like in Sandbox
// we may need to define entry points differently based on platform 


int main(int argc, char** argv)
{

	Crimson::Log::Init();

	CN_PROFILE_BEGIN_SESSION("Init", "CrimsonProfile-Startup.json");
	auto app = Crimson::CreateApplication();
	CN_PROFILE_END_SESSION();

	CN_PROFILE_BEGIN_SESSION("Runtime", "CrimsonProfile-Runtime.json");
	app->Run();
	CN_PROFILE_END_SESSION();

	CN_PROFILE_BEGIN_SESSION("Shutdown", "CrimsonProfile-Shutdown.json");
	delete app;
	CN_PROFILE_END_SESSION();

}

#endif

