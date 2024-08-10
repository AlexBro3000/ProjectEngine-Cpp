#pragma once
#include <glad/glad.h>
#include <string>

class Texture
{
private:
	GLuint ID;
	GLenum slot;

public:
	Texture(const std::string& path, GLenum slot, GLint format, GLenum pxl_format, GLenum pxl_type);
	~Texture();

	void bind();
	void unbind();

	bool is();

private:
};