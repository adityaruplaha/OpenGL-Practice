#include <cstdarg>
#include "program.h"

Log Program::logger = Log("program.log");

Program::Program()
{
	program = glCreateProgram();
	logger.log("A new shader program was created at %n.\n", &program);
}

Program::Program(int shader_count, ...)
{
	program = glCreateProgram();
	logger.log("A new shader program was created at %n.\n", &program);

	va_list args;
	va_start(args, shader_count);
	for (int i = 0; i < shader_count; i++)
	{
		auto shader = va_arg(args, Shader*);
		attach(shader);
	}
	va_end(args);
}

Program::~Program()
{
	glDeleteProgram(program);
}

void Program::attach(Shader* shader)
{
	shaders.push_back(shader);
	glAttachShader(program, shader->get());
}

void Program::link()
{
	glLinkProgram(program);
	int  success;
	char infoLog[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		logger.log("Program at %n failed to be linked.\n%s\n", &program, infoLog);
	}

	for (auto* shader : shaders)
	{
		delete shader;
	}
}

void Program::start()
{
	glUseProgram(program);
}

void Program::stop()
{
	glUseProgram(0);
}