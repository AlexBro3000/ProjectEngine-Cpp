#include "Mesh.h"

Mesh::Mesh() :
	VAO(::VAO()), VBO(::VBO()), vertex_count(0)
{ }

void Mesh::build(const float* vertex_data, size_t vertex_count, const int* attrs, GLenum usage)
{
    int vertex_size = 0;
	for (size_t i = 0; attrs[i] != -1; i++) {
		vertex_size += attrs[i];
	}
    this->vertex_count = vertex_count;

    VAO.bind();
    VBO.bind();

    VBO.setData(vertex_data, vertex_count * vertex_size * sizeof(float), usage);

    int offset = 0;
    for (int i = 0; attrs[i] != -1; i++)
    {
        VAO.linkAttrib(VBO, i, attrs[i], GL_FLOAT, vertex_size * sizeof(float), (void*)(offset * sizeof(float)));
        offset += attrs[i];
    }

    VAO.unbind();
    VBO.unbind();
}

void Mesh::render(GLenum primitive) const
{
    VAO.bind();
    glDrawArrays(primitive, 0, static_cast<GLsizei>(vertex_count));
    VAO.unbind();
}