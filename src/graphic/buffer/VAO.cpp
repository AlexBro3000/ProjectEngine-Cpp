#include "VAO.h"

VAO::VAO() : ID(0)
{
	glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &ID);
}

void VAO::linkAttrib(const VBO& VBO, GLuint layout, GLuint components, GLenum type, GLsizei stride, const void* offset) const
{
	glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
}

void VAO::bind() const
{
	glBindVertexArray(ID);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}