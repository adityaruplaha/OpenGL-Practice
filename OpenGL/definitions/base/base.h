#pragma once

#include <GLinclude/glad/glad.h>
#include <GLinclude/GLFW/glfw3.h>

#include <QuikLog/QuikLog/log.h>

class Initializer {

public:

	static void InitGL()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	}

	static void GLAD_Init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw "Failed to initialize GLAD!\n";
		}
	}
	
};