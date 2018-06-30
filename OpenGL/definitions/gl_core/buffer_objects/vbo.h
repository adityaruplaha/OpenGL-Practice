#pragma once

#include <vector>
#include "../../base/base.h"

class VBO
{
public:
	VBO(std::vector<float> buffer_data, std::vector<int> slice_attribs);	
	void bind();
	GLuint* get();

	static void unbind();

private:
	void slice_using(std::vector<int> attribs);
	void copyFrom(std::vector<float> data);
	float* buffer_data_internal;

	GLuint vbo;
};