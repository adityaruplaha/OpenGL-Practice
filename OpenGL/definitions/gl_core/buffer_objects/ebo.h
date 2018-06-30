#pragma once

#include <vector>
#include "../../base/base.h"

class EBO
{
public:
	EBO(std::vector<GLuint> buffer_data);	
	void bind();
	GLuint* get();

	static void unbind();

private:
	void copyFrom(std::vector<GLuint> data);
	GLuint* buffer_data_internal;

	GLuint ebo;
};