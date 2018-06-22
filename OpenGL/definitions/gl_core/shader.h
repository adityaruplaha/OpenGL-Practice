#pragma once

#include <fstream>
#include <string>
#include "../base/base.h"

class Shader
{
public:
	Shader(std::ifstream stream, int type);
	Shader(std::string src, int type);
	~Shader();

	void compile();
	GLuint get();

private:
	std::string src;
	GLuint shader;
	const int type;

	static std::string getShaderName(int type);

	static Log logger;
};

