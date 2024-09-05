#include "Texture.h"
#include <stb_image.h>

#include "../../graphic/texture/Image.h"
#include "../../system/console/Console.h"

Texture::Texture(GLuint slot, GLuint format)
	: ID(0), slot(slot), format(format), f_texture_loaded(false)
{
	glGenTextures(1, &ID);

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	if (Texture::is()) {
		glDeleteTextures(1, &ID);
		f_texture_loaded = false;
	}
}

void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::is() const
{
	return (ID != 0) && glIsTexture(ID);
}

bool Texture::load(const std::string& path)
{
	if (Texture::is() && f_texture_loaded) {
		Console::Warn("Texture already loaded.", { "Path: " + path });
		return false;
	}

    int width, height, channels;
    unsigned char* data = Image::load(path, &width, &height, &channels);

	if (data) {
		GLenum pxl_format = (channels == 4) ? GL_RGBA : GL_RGB;
		GLenum pxl_type = GL_UNSIGNED_BYTE;

		Texture::bind();
		Texture::loadInitTexture(width, height, pxl_format, pxl_type);
		Texture::loadTextureData(width, height, pxl_format, pxl_type, data);
		Texture::unbind();

		stbi_image_free(data);

        Console::Info("Texture loaded successfully.", { "Path: " + path });
	}
	else {
		Console::Warn("Failed to load texture.", { "Path: " + path });
	}
	return f_texture_loaded;
}

void Texture::loadInitTexture(int width, int height, GLenum pxl_format, GLenum pxl_type)
{
	if (!f_texture_loaded) {
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, pxl_format, pxl_type, NULL);
		f_texture_loaded = true;
	}
}

void Texture::loadTextureData(int width, int height, GLenum pxl_format, GLenum pxl_type, unsigned char* data)
{
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, pxl_format, pxl_type, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}