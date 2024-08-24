#pragma once
#include <glad/glad.h>
#include <string>

class Texture
{
private:
	GLuint ID;
	GLenum slot;
    GLint format;

	bool f_texture_loaded;

	friend class TextureManager;

public:
	Texture(GLenum slot, GLint format);
	~Texture();

	void bind();
	void unbind();

	bool is();

private:
	bool load(const std::string& path);

};