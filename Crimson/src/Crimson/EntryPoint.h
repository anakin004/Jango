#pragma once

#ifdef CN_PLATFORM_WINDOWS

extern Crimson::Application* Crimson::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Crimson::CreateApplication();
	app->Run();
	delete app;
}

#endif

