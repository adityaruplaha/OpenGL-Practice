#pragma once

#include <functional>
#include <vector>
#include "base\base.h"

class InputHandler {

public:
	InputHandler(GLFWwindow* window);
	void attach(GLFWwindow* window);
	void connect(int key, std::function<void ()> func);
	void disconnect(int key);
	void listen();

private:
	GLFWwindow* attached_window;
	std::vector<std::pair<int, std::function<void()>>> binds;
};