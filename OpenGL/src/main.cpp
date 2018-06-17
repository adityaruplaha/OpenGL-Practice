#include <iostream>
#include "definitions/base/base.h"
#include "definitions/window.h"
using namespace std;

int main()
{
	InitGL();
	auto window = Window(800, 600, "test");

	auto* window_ptr = window.getWindow();

	while (!glfwWindowShouldClose(window_ptr))
	{
		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0x1;
}