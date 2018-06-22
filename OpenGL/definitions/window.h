#pragma once

#include <string>
#include "base/base.h"

class Window {

public:

	Window(int width, int height, std::string name);
	void setUp();
	GLFWwindow* getWindowPointer();

private:
	GLFWwindow* window;

};