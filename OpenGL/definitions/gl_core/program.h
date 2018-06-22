#pragma once

#include <vector>
#include "shader.h"

class Program
{
public:
	Program();
	Program(int shader_count, ...);
	~Program();

	void attach(Shader* shader);
	void link();

	void start();
	void stop();

private:
	GLuint program;
	std::vector<Shader*> shaders;

	static Log logger;
};