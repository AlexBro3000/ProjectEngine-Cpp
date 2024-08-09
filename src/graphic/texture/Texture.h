#pragma once
#include <glad/glad.h>
#include <string>

namespace Image
{
	unsigned char* load(const std::string& path, int* width, int* height, int* channels);
};

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