#include "cnpch.h"
#include "OpenGLTime.h"
#include "glad/glad.h"

namespace Crimson {


	double OpenGLGetTime() {
		return glfwGetTime();
	}


}