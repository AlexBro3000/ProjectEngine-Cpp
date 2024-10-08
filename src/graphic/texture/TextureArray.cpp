#include "TextureArray.h"
#include <stb_image.h>

#include "../../graphic/texture/Image.h"
#include "../../system/console/Console.h"

TextureArray::TextureArray(GLuint slot, GLuint format, int width, int height, int depth)
    : ID(0), slot(slot), format(format), f_texture_loaded(false), width(width), height(height), depth(depth), size(0)
{
    glGenTextures(1, &ID);

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

TextureArray::~TextureArray()
{
	if (TextureArray::is()) {
		glDeleteTextures(1, &ID);
        f_texture_loaded = false;
	}
}

void TextureArray::bind() const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
}

void TextureArray::unbind() const
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

bool TextureArray::is() const
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
        GLenum pxl_format = (channels == 4) ? GL_RGBA : GL_RGB;
        GLenum pxl_type = GL_UNSIGNED_BYTE;

        int max_layers = width / TextureArray::width * height / TextureArray::height;

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
        TextureArray::loadInitTexture(TextureArray::width, TextureArray::height, pxl_format, pxl_type);
        TextureArray::loadTextureData(TextureArray::width, TextureArray::height, pxl_format, pxl_type, data, width, height, channels, layers);
        TextureArray::unbind();

        stbi_image_free(data);

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

void TextureArray::loadInitTexture(int width, int height, GLenum pxl_format, GLenum pxl_type)
{
    if (!f_texture_loaded) {
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, format, width, height, depth, 0, pxl_format, pxl_type, NULL);
        f_texture_loaded = true;
    }
}

void TextureArray::loadTextureData(int width, int height, GLenum pxl_format, GLenum pxl_type, unsigned char* data, int img_width, int img_height, int channels, int layers)
{
    int tiles_x = img_width / width;
    int tiles_y = img_height / height;

    for (int depth = 0; depth < layers; depth++) {
        unsigned char* data_tmp = new unsigned char[width * height * channels];
        int shift = (depth % tiles_x) + (tiles_y - (depth / tiles_x + 1)) * tiles_x;

        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                int index = (w + h * img_width + (shift % tiles_x) * width + (shift / tiles_y) * (img_width * height)) * channels;
                for (int c = 0; c < channels; c++) {
                    data_tmp[c + (w + h * width) * channels] = data[c + index];
                }
            }
        }

        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, size + depth, width, height, 1, pxl_format, pxl_type, data_tmp);
        delete[] data_tmp;
    }

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    size += layers;
}