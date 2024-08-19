#pragma once
#include <glad/glad.h>
#include <string>

class Texture
{
private:
	GLuint ID;
	GLenum slot;

	friend class TextureManager;

public:
	Texture(const std::string& path, GLenum slot, GLint format);
	~Texture();

	void bind();
	void unbind();

	bool is();

private:
};