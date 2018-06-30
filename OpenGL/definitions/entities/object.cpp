#include "object.h"

Object::Object(Vertices v, Indices i, std::vector<int> slices) : v(v), indexSize(i.size())
{
	LOG_INFO("New object created at memory address 0x%p.", this);
	vao = VAO();
	if (slices == std::vector<int>())
	{
		LOG_WARNING("0x%p: Slicing attributes not set! Determining them programmatically...", this);
		for (Attribute attrib : (this->v)[0])
		{
			slices.push_back(attrib.size());
		}
	}
	VBO vbo = VBO(flatten(), slices);
	EBO ebo = EBO(i);
}

void Object::render()
{
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
}

std::vector<float> Object::flatten()
{
	std::vector<float> t;
	for (auto vertex : this->v)
	{
		for (auto attrib : vertex)
		{
			for (auto val : attrib)
			{
				t.push_back(val);
			}
		}
	}
	return t;
}