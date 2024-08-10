#pragma once
#include <glad/glad.h>
#include "VBO.h"

class VAO
{
private:
	GLuint ID;

public:
	VAO();
	~VAO();

	void linkAttrib(const VBO& VBO, GLuint layout, GLuint components, GLenum type, GLsizei stride, const void* offset) const;

	void bind() const;
	void unbind() const;

private:
	VAO(const VAO&) = delete;
	VAO(VAO&&) = delete;

	VAO& operator=(const VAO&) = delete;
	VAO& operator=(VAO&&) = delete;
};