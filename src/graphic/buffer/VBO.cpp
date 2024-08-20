#include "VBO.h"

VBO::VBO() : ID(0)
{
	glGenBuffers(1, &ID);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &ID);
}

void VBO::setData(const void* data, GLsizeiptr size, GLenum usage) const
{
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VBO::updateData(GLintptr offset, const void* data, GLsizeiptr size) const
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VBO::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}