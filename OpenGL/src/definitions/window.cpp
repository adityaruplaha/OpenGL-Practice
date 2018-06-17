#include "window.h"

Window::Window(int width, int height, std::string name)
{
	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		throw "Failed to create GLFW window\n";
	}
	glfwMakeContextCurrent(window);

	// Check for functioning GLAD systems.
#ifndef GLAD_CHECK_SUCCESSFUL
	GLAD_Init();
#endif // !GLAD_CHECK_SUCCESSFUL	

	glfwSetFramebufferSizeCallback(window,
		[](GLFWwindow*, int w, int h)
	{
		glViewport(0, 0, w, h);
	});
}

GLFWwindow* Window::getWindow()
{
	return window;
}