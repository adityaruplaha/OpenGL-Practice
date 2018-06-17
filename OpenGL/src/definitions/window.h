#pragma once

#include <string>
#include "base/base.h"

class Window {

public:

	Window(int width, int height, std::string name);

	GLFWwindow* getWindow();

private:
	GLFWwindow* window;

};