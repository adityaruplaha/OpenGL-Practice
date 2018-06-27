#include "window.h"

Window::Window(int width, int height, std::string name)
{
	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		LOG_CRITICAL("Failed to create GLFW window\n");
	}
	glfwMakeContextCurrent(window);
}

void Window::setUp()
{
	glfwSetFramebufferSizeCallback(window,
		[](GLFWwindow*, int w, int h)
	{
		glViewport(0, 0, w, h);
	});
}

GLFWwindow* Window::getWindowPointer()
{
	return window;
}