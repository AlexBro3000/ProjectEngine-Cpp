#pragma once
#include "../../graphic/buffer/VAO.h"
#include "../../graphic/buffer/VBO.h"

class Mesh
{
private:
	VAO VAO;
	VBO VBO;
	size_t vertex_count;

public:
	Mesh();
	~Mesh() = default;

	void build(const float* vertex_data, size_t vertex_count, const int* attrs, GLenum usage);
	void render(GLenum primitive = GL_TRIANGLES) const;

private:

};