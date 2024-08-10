#include "VBO.h"

VBO::VBO() :
    ID(0)
{
	glGenBuffers(1, &ID);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &ID);
}

void VBO::setData(const void* data, GLsizeiptr size, GLenum usage) const
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    unbind();
}

void VBO::updateData(GLintptr offset, const void* data, GLsizeiptr size) const
{
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    unbind();
}

void VBO::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}