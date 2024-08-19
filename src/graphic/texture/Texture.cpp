#include "Texture.h"
#include "../../graphic/texture/Image.h"
#include "../../system/console/Console.h"
#include <stb_image.h>

Texture::Texture(const std::string& path, GLenum slot, GLint format) :
	ID(0), slot(slot)
{
	int width, height, channels;
	unsigned char* data = Image::load(path, &width, &height, &channels);

	GLenum pxl_format = (channels == 4) ? GL_RGBA : GL_RGB;
	GLenum pxl_type= GL_UNSIGNED_BYTE;

	if (data) {
		glGenTextures(1, &ID);

		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, pxl_format, pxl_type, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Установка параметров текстуры
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
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