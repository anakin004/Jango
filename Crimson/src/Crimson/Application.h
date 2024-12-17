#pragma once

#include "Core.h"

namespace Crimson {


	class CRIMSON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};


	// to be defined in client
	Application* CreateApplication();


}
