#pragma once

#include <vector>
#include "../gl_core/buffer_objects.h"

typedef std::vector<float> Attribute;
typedef std::vector<Attribute> Vertex;
typedef std::vector<Vertex> Vertices;

typedef std::vector<GLuint> Indices;

class Object
{
public:
	Object(Vertices v, Indices i, std::vector<int> slices = std::vector<int>());
	void render();

private:
	VAO vao;
	Vertices v;
	const int indexSize;
	std::vector<float> flatten();
};