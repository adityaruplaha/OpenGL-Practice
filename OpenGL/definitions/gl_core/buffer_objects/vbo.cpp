#include "vbo.h"

VBO::VBO(std::vector<float> buffer_data, std::vector<int> slice_attribs)
{
	glGenBuffers(1, &vbo);
	LOG_SUCCESS("New VBO created at 0x%p.", &vbo);
	bind();
	if (!buffer_data.size())
	{
		LOG_ERROR("0x%p: Empty buffer passed as a argument.", &vbo);
	}
	copyFrom(buffer_data);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_data.size(), buffer_data_internal, GL_STATIC_DRAW);
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

void VBO::slice_using(std::vector<int> slice_attribs)
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

void VBO::copyFrom(std::vector<float> data)
{
	auto size = data.size();
	buffer_data_internal = new float[size];
	int i = 0;
	for (i = 0; i < data.size(); i++)
	{
		buffer_data_internal[i] = data[i];
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