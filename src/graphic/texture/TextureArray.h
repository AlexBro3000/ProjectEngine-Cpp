#pragma once
#include <glad/glad.h>
#include <string>

class TextureArray {
private:
    GLuint ID;
    GLuint slot, format;

    bool f_texture_loaded;

    int width, height, depth;
    int size;

    friend class TextureManager;

public:
    TextureArray(GLuint slot, GLuint format, int width, int height, int depth);
    ~TextureArray();

    void bind() const;
    void unbind() const;

    bool is() const;

private:
    bool load(const std::string& path, int layers);
    void loadInitTexture(int width, int height, GLenum pxl_format, GLenum pxl_type);
    void loadTextureData(int width, int height, GLenum pxl_format, GLenum pxl_type, unsigned char* data, int img_width, int img_height, int channels, int layers);

};