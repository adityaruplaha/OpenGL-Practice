#pragma once

#include "../base/base.h"

class VBO
{
public:
	VBO(float* buffer_data);
	VBO(float* buffer_data, std::initializer_list<int> slice_attribs);
	void slice_using(std::initializer_list<int> attribs);
	void bind();
	GLuint* get();

	static void unbind();

private:
	GLuint vbo;
};