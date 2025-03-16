#include "cnpch.h"

#include "Crimson/Core/Subsystems.h"
#include "Crimson/Core/Log.h"
#include <GLFW/glfw3.h>

namespace Crimson {

	bool Subsystems::s_GLFWBooted = false;
	bool Subsystems::s_GLFWTerminated = false;

	void Subsystems::InitGL() {

		CN_PROFILE_FUNCTION()

		if (s_GLFWBooted == false)
		{
			// need to terminate glfw, but not when we destruct window
			// we may have multiple windows
			int success = glfwInit();
			CN_CORE_ASSERT(success, "GLFW Failed To Initalized!");
			CN_CORE_INFO("GLFW Initialized");
			glfwSetErrorCallback(GLFWErrorCallBack);

			s_GLFWBooted = true;
		}

	}

	// will figure out handling destruction of textures, buffers, etc elsewhere
	void Subsystems::ShutDownGL() {
		if (!s_GLFWTerminated) {
			glfwTerminate();
			CN_CORE_INFO("GLFW Terminated!");
			s_GLFWTerminated = true;
		}
	}

	void Subsystems::GLFWErrorCallBack(int error, const char* description) {
		CN_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}


}
