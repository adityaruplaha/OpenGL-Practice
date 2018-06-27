#include <sstream>
#include <iostream>

#include "shader.h"

Shader::Shader(std::string src, int type) : src(src), type(type)
{
	shader = glCreateShader(this->type);
	LOG_INFO("A new %s was created at 0x%p.", getShaderName(this->type).c_str(), &shader);
	if (this->src.empty())
	{
		LOG_ERROR("0x%p: Shader is blank!", &shader);
	}
}

Shader::Shader(std::ifstream stream, int type) : type(type)
{
	shader = glCreateShader(this->type);
	LOG_INFO("A new %s was created at 0x%p.", getShaderName(this->type).c_str(), &shader);

	std::ostringstream ss;
	ss << stream.rdbuf();
	src = ss.str();
	if (src.empty())
	{
		LOG_ERROR("0x%p: Shader is blank!", &shader);
	}
}

Shader::~Shader()
{
	shader = glCreateShader(type);
	LOG_INFO("0x%p: Shader deleted.", getShaderName(type), &shader);

	glDeleteShader(shader);
}

void Shader::compile()
{
	auto src_char_pointer = src.c_str();
	glShaderSource(shader, 1, &src_char_pointer, NULL);
	glCompileShader(shader);

	int  success;
	char infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		LOG_ERROR("Shader compilation for %s at 0x%p failed.\n%s", getShaderName(type).c_str(), &shader, infoLog);
		return;
	}
	LOG_SUCCESS("%s at 0x%p was compiled successfully.", getShaderName(type).c_str(), &shader);
	is_compiled = true;
}
GLuint Shader::get()
{
	return shader;
}

std::string Shader::getShaderName(int type)
{
	switch (type)
	{
	case(GL_VERTEX_SHADER):
		return "VERTEX_SHADER";
	case(GL_FRAGMENT_SHADER):
		return "FRAGMENT_SHADER";
	case(GL_GEOMETRY_SHADER):
		return "GEOMETRY_SHADER";
	case(GL_TESS_CONTROL_SHADER):
		return "TESSELATION_CONTROL_SHADER";
	case(GL_TESS_EVALUATION_SHADER):
		return "TESSELATION_EVALUATION_SHADER";
	case(GL_COMPUTE_SHADER):
		return "COMPUTE_SHADER";
	default:
		return "UNKNOWN_SHADER";
	}
}
