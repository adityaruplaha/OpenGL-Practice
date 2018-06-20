#include <algorithm>
#include "input_handler.h"

InputHandler::InputHandler(GLFWwindow* window)
{
	attach(window);
}

void InputHandler::attach(GLFWwindow* window)
{
	attached_window = window;
}

void InputHandler::connect(int key, std::function<void()> func)
{
	auto pair = std::make_pair(key, func);
	binds.push_back(pair);
}

void InputHandler::disconnect(int key)
{
	for (int i = 0; i < binds.size(); i++)
	{
		if (binds[i].first == key)
			binds.erase(binds.begin() + i);

		break;
	}
}

void InputHandler::listen()
{
	for (auto b : binds)
	{
		if (glfwGetKey(attached_window, b.first) == GLFW_PRESS)
			(b.second)();
	}
}