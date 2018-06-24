#pragma once

#include "../base/base.h"

class VAO
{
public:
	VAO();
	void bind();

	static void unbind();

private:
	GLuint vao;
};