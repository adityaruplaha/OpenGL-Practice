#include "vbo.h"

VBO::VBO(float* buffer_data)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
}

VBO::VBO(float* buffer_data, std::initializer_list<int> slice_attribs)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);

	slice_using(slice_attribs);
}

void VBO::slice_using(std::initializer_list<int> slice_attribs)
{
	// bind just in case it was unbound earlier;
	bind();

	int i = 0;
	int offset = 0;

	// determine stride
	int stride = 0;
	for (auto size : slice_attribs)
	{
		stride += size;
	}

	for (auto size : slice_attribs)
	{
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		i++;
		offset += size;
	}
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint* VBO::get()
{
	return &vbo;
}