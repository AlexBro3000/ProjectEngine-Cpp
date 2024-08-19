#include "TextureArray.h"
#include "../../graphic/texture/Image.h"
#include "../../system/console/Console.h"
#include <stb_image.h>

TextureArray::TextureArray(GLenum slot, GLint format, GLsizei width, GLsizei height, GLsizei depth)
    : ID(0), slot(slot), format(format), width(width), height(height), depth(depth), size(0)
{
    glGenTextures(1, &ID);

    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, format, width, height, depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    // Установка параметров текстуры
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

TextureArray::~TextureArray()
{
	if (TextureArray::is()) {
		glDeleteTextures(1, &ID);
	}
}

void TextureArray::bind()
{
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
}

void TextureArray::unbind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

bool TextureArray::is()
{
	return (ID != 0) && glIsTexture(ID);
}


void TextureArray::loadTexture(const std::string& path, int layers)
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);

    int width, height, channels;
    unsigned char* t_data = Image::load(path, &width, &height, &channels);

    if (t_data) {
        int tiles_x = width / TextureArray::width;
        int tiles_y = height / TextureArray::height;
        int max_layers = tiles_x * tiles_y;

        if (layers > max_layers) {
            Console::Warn("TEXTURE_ARRAY", { "The number of layers exceeds the available layers in the image. Using the maximum number available." });
            layers = max_layers;
        }

        if (size + layers > depth) {
            Console::Warn("TEXTURE_ARRAY", { "There is not enough space in the texture array. Reduce the number of available layers." });
            layers = depth - size;
        }

        GLenum pxl_format = (channels == 4) ? GL_RGBA : GL_RGB;
        GLenum pxl_type = GL_UNSIGNED_BYTE;

        for (int depth = 0; depth < layers; depth++) {
            unsigned char* data_tmp = new unsigned char[TextureArray::width * TextureArray::height * channels];

            int shift = (depth % tiles_x) + (tiles_y - (depth / tiles_x + 1)) * tiles_x;

            for (int h = 0; h < TextureArray::height; h++) {
                for (int w = 0; w < TextureArray::width; w++) {
                    int index = (w + h * width + (shift % tiles_x) * TextureArray::width + (shift / tiles_y) * (width * TextureArray::height)) * channels;

                    for (int c = 0; c < channels; c++) {
                        data_tmp[c + (w + h * TextureArray::width) * channels] = t_data[c + index];
                    }
                }
            }

            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, size + depth, TextureArray::width, TextureArray::height, 1, pxl_format, pxl_type, data_tmp);

            delete[] data_tmp;
        }

        size += layers;
        glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    }
    else {
        Console::Warn("TEXTURE_ARRAY", { "Failed to load texture: " + path });
    }

    stbi_image_free(t_data);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}