#include <iostream>
#include "definitions/base/base.h"
#include "definitions/window.h"
#include "definitions/input_handler.h"
using namespace std;

int main()
{
	Log logger = Log("main.log");
	Initializer::InitGL();

	auto* window = new Window(800, 600, "test");
	Initializer::GLAD_Init();
	window->setUp();

	auto* window_ptr = window->getWindowPointer();
	auto* handler = new InputHandler(window_ptr);

	handler->connect(GLFW_KEY_ESCAPE,
		[&window_ptr]() {glfwSetWindowShouldClose(window_ptr, true); }
	);

	logger.log("test log");

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	while (!glfwWindowShouldClose(window_ptr))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		handler->listen();

		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0x1;
}