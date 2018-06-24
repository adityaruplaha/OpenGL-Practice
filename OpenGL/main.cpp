#include <iostream>
#include "definitions/window.h"
#include "definitions/input_handler.h"
#include "definitions/gl_core/program.h"
#include "definitions/gl_core/vbo.h"
#include "definitions/gl_core/vao.h"
using namespace std;

const char *vertexShaderSource = "#version 430 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 430 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	Initializer::InitGL();

	auto log_name = "Main";

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
	vao.bind();
	auto vbo = VBO(vertices, { 3 });
	VBO::unbind();
	VAO::unbind();

	auto* vs = new Shader(vertexShaderSource, GL_VERTEX_SHADER);
	vs->compile();
	auto* fs = new Shader(fragmentShaderSource, GL_FRAGMENT_SHADER);
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

		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0x1;
}