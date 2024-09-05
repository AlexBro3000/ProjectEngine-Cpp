#pragma once
#include <glad/glad.h>
#include <string>

class Texture {
private:
	GLuint ID;
	GLuint slot, format;

	bool f_texture_loaded;

	friend class TextureManager;

public:
	Texture(GLuint slot, GLuint format);
	~Texture();

	void bind() const;
	void unbind() const;

	bool is() const;

private:
	bool load(const std::string& path);
	void loadInitTexture(int width, int height, GLenum pxl_format, GLenum pxl_type);
	void loadTextureData(int width, int height, GLenum pxl_format, GLenum pxl_type, unsigned char* data);

};