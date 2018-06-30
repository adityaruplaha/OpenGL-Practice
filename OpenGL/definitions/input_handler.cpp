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

void InputHandler::connect(std::vector<int> keys, std::function<void()> func)
{
	auto pair = std::make_pair(keys, func);
	binds_m.push_back(pair);
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

void InputHandler::disconnect(std::vector<int> keys)
{
	for (int i = 0; i < binds_m.size(); i++)
	{
		if (binds_m[i].first == keys)
			binds_m.erase(binds_m.begin() + i);

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

	for (auto b : binds_m)
	{
		bool active = true;
		for (auto k : b.first)
		{
			active = active && (glfwGetKey(attached_window, k) == GLFW_PRESS);
		}
		if (active)
		{
			(b.second)();
		}
	}
}