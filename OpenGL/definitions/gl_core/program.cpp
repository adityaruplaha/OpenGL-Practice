#include <cstdarg>
#include "program.h"

Program::Program()
{
	program = glCreateProgram();
	LOG_INFO("A new shader program was created at 0x%p.", &program);
}

Program::Program(int shader_count, ...)
{
	program = glCreateProgram();
	LOG_INFO("A new shader program was created at 0x%p.", &program);

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
}

void Program::link()
{
	for (auto shader : shaders)
	{
		if (!shader->is_compiled)
		{
			LOG_WARNING("0x%p: A shader wasn't pre-compiled. Compiling it now...", &program);
			shader->compile();
			if (!shader->is_compiled)
			{
				LOG_CRITICAL("0x%p: Shader couldn't be compiled!", &program);
			}
		}
		glAttachShader(program, shader->get());
	}

	glLinkProgram(program);

	int  success;
	char infoLog[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		LOG_ERROR("Program at 0x%p failed to be linked.\n%s", &program, infoLog);
		return;
	}
	LOG_SUCCESS("Program at 0x%p was linked successfully.", &program);
}

void Program::start()
{
	glUseProgram(program);
}

void Program::stop()
{
	glUseProgram(0);
}