#include "TextureArray.h"
#include "../../graphic/texture/Image.h"
#include "../../system/console/Console.h"
#include <stb_image.h>

TextureArray::TextureArray(GLenum slot, GLint format, int width, int height, int depth)
    : ID(0), slot(slot), format(format), width(width), height(height), depth(depth), size(0), f_texture_loaded(false)
{
    glGenTextures(1, &ID);

    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

TextureArray::~TextureArray()
{
	if (TextureArray::is()) {
		glDeleteTextures(1, &ID);
        f_texture_loaded = false;
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

bool TextureArray::load(const std::string& path, int layers)
{
    if (TextureArray::is() && f_texture_loaded && depth == size) {
        Console::Warn("Texture array already loaded.", { "Path: " + path });
        return false;
    }

    int width, height, channels;
    unsigned char* data = Image::load(path, &width, &height, &channels);

    if (data) {
        int max_layers = width / TextureArray::width * height / TextureArray::height;
        GLenum pxl_format = (channels == 4) ? GL_RGBA : GL_RGB;
        GLenum pxl_type = GL_UNSIGNED_BYTE;

        if (layers > max_layers) {
            Console::Warn("The number of layers exceeds the available layers in the image. The maximum number of layers available will be used.", {
                "Layers: " + std::to_string(layers) + " >> " + std::to_string(max_layers)
                });
            layers = max_layers;
        }
        if (size + layers > depth) {
            Console::Warn("There is not enough space in the texture array. The maximum number of layers available will be used.", {
                "Layers: " + std::to_string(layers) + " >> " + std::to_string(depth - size)
                });
            layers = depth - size;
        }

        TextureArray::bind();
        TextureArray::loadInitTextureArray();
        TextureArray::loadLayers(data, width, height, channels, layers);
        TextureArray::unbind();

        stbi_image_free(data);
        f_texture_loaded = true;
        size += layers;

        Console::Info("Texture array loaded successfully.", {
            "Path:   " + path,
            "Layers: " + std::to_string(layers) + " (" + std::to_string(size) + " / " + std::to_string(depth) + ")"
            });
    }
    else {
        Console::Warn("Failed to load texture.", { "Path: " + path });
    }
    return f_texture_loaded;
}

void TextureArray::loadInitTextureArray()
{
    if (!f_texture_loaded) {
        glTexImage3D(
            GL_TEXTURE_2D_ARRAY, 0, TextureArray::format,
            TextureArray::width, TextureArray::height, TextureArray::depth, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, NULL
        );
    }
}

void TextureArray::loadLayers(unsigned char* data, int width, int height, int channels, int layers)
{
    int tiles_x = width / TextureArray::width;
    int tiles_y = height / TextureArray::height;

    for (int depth = 0; depth < layers; depth++) {
        unsigned char* data_tmp = new unsigned char[TextureArray::width * TextureArray::height * channels];
        int shift = (depth % tiles_x) + (tiles_y - (depth / tiles_x + 1)) * tiles_x;

        for (int h = 0; h < TextureArray::height; h++) {
            for (int w = 0; w < TextureArray::width; w++) {
                int index = (w + h * width + (shift % tiles_x) * TextureArray::width + (shift / tiles_y) * (width * TextureArray::height)) * channels;
                for (int c = 0; c < channels; c++) {
                    data_tmp[c + (w + h * TextureArray::width) * channels] = data[c + index];
                }
            }
        }

        glTexSubImage3D(
            GL_TEXTURE_2D_ARRAY, 0, 0, 0, size + depth,
            TextureArray::width, TextureArray::height, 1, (channels == 4) ? GL_RGBA : GL_RGB,
            GL_UNSIGNED_BYTE, data_tmp
        );
        delete[] data_tmp;
    }
}