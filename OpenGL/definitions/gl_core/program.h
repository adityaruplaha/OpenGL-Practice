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

	void setBool(std::string name, bool b);
	void setFloat(std::string name, float f);
	void setInt(std::string name, int i);
	void setVec2(std::string name, float f1, float f2);
	void setVec3(std::string name, float f1, float f2, float f3);
	void setVec4(std::string name, float f1, float f2, float f3, float f4);

private:
	GLuint program;
	std::vector<Shader*> shaders;
};