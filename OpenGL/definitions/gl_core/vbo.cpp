#include "vbo.h"

VBO::VBO(float* buffer_data)
{
	glGenBuffers(1, &vbo);
	LOG_SUCCESS("New VBO created at 0x%p.", &vbo);
	bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
	if (glGetError() == GL_NO_ERROR)
	{
		LOG_SUCCESS("0x%p: Buffer data initialized successfully.", &vbo);
	}
}

VBO::VBO(float* buffer_data, std::initializer_list<int> slice_attribs)
{
	glGenBuffers(1, &vbo);
	LOG_SUCCESS("New VBO created at 0x%p.", &vbo);
	bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
	if (glGetError() == GL_NO_ERROR)
	{
		LOG_SUCCESS("0x%p: Buffer data initialized successfully.", &vbo);
	}
	else
	{
		LOG_ERROR("0x%p: Buffer data was NOT initialized successfully.", &vbo);
	}

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
	LOG_INFO("0x%p: Buffer stride determined as %i.", &vbo, stride);

	for (auto size : slice_attribs)
	{
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		if (glGetError() == GL_NO_ERROR)
		{
			LOG_SUCCESS("0x%p: Sliced %i values at [offset=0x%i] for attribute (location=%i).", &vbo, size, offset, i);
		}
		else
		{
			LOG_ERROR("0x%p: Unable to slice for attribute location %i.", &vbo, i);
		}
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