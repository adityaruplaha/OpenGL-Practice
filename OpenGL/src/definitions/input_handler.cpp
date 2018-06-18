#include "input_handler.h"

InputHandler::InputHandler(GLFWwindow* window)
{
	attach(window);
}

void InputHandler::attach(GLFWwindow* window)
{
	attached_window = window;
}

void InputHandler::handle(int key, std::function<void()> func)
{
	binds_.push_back(std::make_pair(key, func));
}

void InputHandler::handle(std::vector<std::pair<int, std::function<void()>>> binds)
{
	for (auto e : binds)
	{
		binds_.push_back(e);
	}
}

void InputHandler::listen()
{
	for (auto b : binds_)
	{
		if (glfwGetKey(attached_window, b.first) == GLFW_PRESS)
			(b.second)();
	}
}