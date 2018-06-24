#include <cstdarg>
#include "program.h"

const std::string Program::log_name = "GLProgram";

Program::Program()
{
	program = glCreateProgram();
	LOG_INFO(log_name, "A new shader program was created at %n.\n", &program);
}

Program::Program(int shader_count, ...)
{
	program = glCreateProgram();
	LOG_INFO(log_name, "A new shader program was created at %n.\n", &program);

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
			LOG_WARNING(log_name, "%n: A shader wasn't pre-compiled. Compiling it now...", &program);
			shader->compile();
			if (!shader->is_compiled)
			{
				LOG_CRITICAL(log_name, "%n: Shader couldn't be compiled!", &program);
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
		LOG_ERROR(log_name, "Program at %n failed to be linked.\n%s\n", &program, infoLog);
	}
	LOG_SUCCESS(log_name, "Program at %n was linked successfully.", &program);
}

void Program::start()
{
	glUseProgram(program);
}

void Program::stop()
{
	glUseProgram(0);
}