#include "ebo.h"

EBO::EBO(std::vector<GLuint> buffer_data)
{
	glGenBuffers(1, &ebo);
	LOG_SUCCESS("New EBO created at 0x%p.", &ebo);
	bind();
	if (!buffer_data.size())
	{
		LOG_ERROR("0x%p: Empty buffer passed as a argument.", &ebo);
	}
	copyFrom(buffer_data);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * buffer_data.size(), buffer_data_internal, GL_STATIC_DRAW);
	if (glGetError() == GL_NO_ERROR)
	{
		LOG_SUCCESS("0x%p: Buffer data initialized successfully.", &ebo);
	}
	else
	{
		LOG_ERROR("0x%p: Buffer data was NOT initialized successfully.", &ebo);
	}
}

void EBO::copyFrom(std::vector<GLuint> data)
{
	auto size = data.size();
	buffer_data_internal = new GLuint[size];
	int i = 0;
	for (i = 0; i < data.size(); i++)
	{
		buffer_data_internal[i] = data[i];
	}
}

void EBO::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void EBO::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint* EBO::get()
{
	return &ebo;
}