#pragma once
#include<glad/glad.h>

class VBO
{
private:
	GLuint ID;

public:
	VBO();
	~VBO();

	void setData(const void* data, GLsizeiptr size, GLenum usage) const;
	void updateData(GLintptr offset, const void* data, GLsizeiptr size) const;

	void bind() const;
	void unbind() const;

private:
	VBO(const VBO&) = delete;
	VBO(VBO&&) = delete;

	VBO& operator=(const VBO&) = delete;
	VBO& operator=(VBO&&) = delete;
};
