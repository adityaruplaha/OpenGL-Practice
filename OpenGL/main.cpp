#include <iostream>
#include "definitions/window.h"
#include "definitions/input_handler.h"
#include "definitions/gl_core/program.h"
#include "definitions/entities/object.h"
using namespace std;

int main()
{
	Initializer::InitGL();

	REGISTER_LOG_FILE(new std::ofstream("../logs/log.log"));

	auto* window = new Window(800, 600, "test");
	Initializer::GLAD_Init();
	window->setUp();

	auto* window_ptr = window->getWindowPointer();
	auto* handler = new InputHandler(window_ptr);

	handler->connect(GLFW_KEY_ESCAPE,
		[&window_ptr]() {glfwSetWindowShouldClose(window_ptr, true); }
	);

	Vertices vertices = {
	{{0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},  // top right
	{{0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}},  // bottom right
	{{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},  // bottom left
	{{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}  // top left 
	};

	Indices indices = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	auto* rect = new Object(vertices, indices);

	auto* vs = new Shader(std::ifstream("../shaders/uni_vert.vert"), GL_VERTEX_SHADER);
	auto* fs = new Shader(std::ifstream("../shaders/uni_frag.frag"), GL_FRAGMENT_SHADER);

	auto prog = new Program(2, vs, fs);
	prog->link();
	prog->start();
	
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	while (!glfwWindowShouldClose(window_ptr))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		handler->listen();

		prog->setVec3("color", 0.0f, sin(glfwGetTime()) / 2.0f + 0.5f, 0.0f);

		rect->render();

		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}

	LOG_INFO("Terminating...");
	glfwTerminate();
	return 0x1;
}