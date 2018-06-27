#include <iostream>
#include "definitions/window.h"
#include "definitions/input_handler.h"
#include "definitions/gl_core/program.h"
#include "definitions/gl_core/vbo.h"
#include "definitions/gl_core/vao.h"
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

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	auto vao = VAO();
	auto vbo = VBO(vertices, { 3 });

	auto* vs = new Shader(std::ifstream("../shaders/vertex.vert"), GL_VERTEX_SHADER);
	vs->compile();
	auto* fs = new Shader(std::ifstream("../shaders/fragment.frag"), GL_FRAGMENT_SHADER);
	fs->compile();

	auto prog = new Program(2, vs, fs);
	prog->link();
	prog->start();
	
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	while (!glfwWindowShouldClose(window_ptr))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		handler->listen();

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0x1;
}