#include "Texture.h"
#include "../../system/console/Console.h"
#include <stb_image.h>

////////////////////////////////////////////////////////////////////////////////
/////   IMAGE                                                              /////
////////////////////////////////////////////////////////////////////////////////

unsigned char* Image::load(const std::string& path, int* width, int* height, int* channels)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), width, height, channels, 0);

	if (data) {
		Console::Info("The texture file was read successfully.",
			{ "Path: " + path });
	}
	else {
		Console::Warn("Failed to read texture file.",
			{ "Path: " + path });
	}
	return data;
}

////////////////////////////////////////////////////////////////////////////////
/////   TEXTURE                                                            /////
////////////////////////////////////////////////////////////////////////////////

Texture::Texture(const std::string& path, GLenum slot, GLint format, GLenum pxl_format, GLenum pxl_type) :
	ID(0), slot(slot)
{
	int width, height, channels;
	unsigned char* data = Image::load(path, &width, &height, &channels);

	if (data) {
		glGenTextures(1, &ID);

		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, pxl_format, pxl_type, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		// Установка параметров текстуры
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

Texture::~Texture()
{
	if (Texture::is()) {
		glDeleteTextures(1, &ID);
	}
}

void Texture::bind()
{
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::is()
{
	return (ID != 0) && glIsTexture(ID);
}