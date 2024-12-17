#pragma once

#ifdef CN_PLATFORM_WINDOWS

extern Crimson::Application* Crimson::CreateApplication();

int main(int argc, char** argv)
{

	Crimson::Log::Init();
	CN_CORE_CRITICAL("Critical Error");
	int a = 1;
	CN_CORE_INFO("Var = {0}", a);

	auto app = Crimson::CreateApplication();
	app->Run();
	delete app;
}

#endif

