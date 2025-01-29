#pragma once

namespace Crimson {

	class Subsystems {
	public:

		static void ShutDownGL();
		static void InitGL();
		static void GLFWErrorCallBack(int error, const char* description);

	private:
		static bool s_GLFWBooted;
		static bool s_GLFWTerminated;
	};

}
