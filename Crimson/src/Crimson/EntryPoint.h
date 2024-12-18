#pragma once

#ifdef CN_PLATFORM_WINDOWS

extern Crimson::Application* Crimson::CreateApplication();


// allows us to define our entry pointer seperate from application, like in Sandbox
// we may need to define entry points differently based on platform 


int main(int argc, char** argv)
{

	Crimson::Log::Init();

	int a = 1;
	CN_CORE_INFO("Var = {0}", a);
	CN_CORE_CRITICAL("melvin");

	auto app = Crimson::CreateApplication();
	app->Run();
	delete app;
}

#endif

