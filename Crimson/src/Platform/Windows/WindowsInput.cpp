#include "cnpch.h"
#include "WindowsInput.h"
#include "Crimson/Application.h"

#include <GLFW/glfw3.h>

namespace Crimson {

	// Input is completely static and has no data, does no initilization
	 
	
	/* 
	   ~  a note regarding the use of pointers for static variables in areas of engine

		  For starters it allows for lazy initalization, like in the application class
		  since there is one instance of the crimson engine, we can asign it to be first
		  creation of the application, being when sandbox is created

		  another reason, from what I have read, when you export a non-pointer static variable from a DLL, 
		  each module (the DLL and the main application) might end up with its own copy of the variable
		  This can lead to inconsistencies where changes in one module aren't reflected in the other 

		  If you use a pointer, both the DLL and the main application refer to the same object
		  if you use a direct object, each might have its own copy, 
		  leading to inconsistencies.
	*/  


	// also need to free this for good measure, there is no data but there is still v-table

	Input* Input::s_Instance = new WindowsInput();


	bool WindowsInput::IsKeyPressedImpl(int keycode) const
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl() const
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) const
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl() const 
	{
		// structured binding is so cool, I had to say it
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl() const
	{
		auto [x, y] = GetMousePosImpl();
		return y;
	}

}
