#include <iostream>
#include "definitions/base/base.h"
#include "definitions/window.h"
using namespace std;

int main()
{
	InitGL();
	auto window = Window(800, 600, "test");

	auto* window_ptr = window.getWindowPointer();

	GLAD_Init();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while (!glfwWindowShouldClose(window_ptr))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0x1;
}