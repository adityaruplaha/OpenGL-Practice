#include "vao.h"

VAO::VAO()
{
	glGenVertexArrays(1, &vao);
}


void VAO::bind()
{
	glBindVertexArray(vao);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}