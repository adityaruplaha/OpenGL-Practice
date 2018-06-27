#include "vao.h"

VAO::VAO()
{
	glGenVertexArrays(1, &vao);
	LOG_SUCCESS("New VAO created at 0x%p.", &vao);
	bind();
}


void VAO::bind()
{
	glBindVertexArray(vao);
	LOG_INFO("%p: VAO bound.", &vao);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}