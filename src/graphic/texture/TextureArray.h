#pragma once
#include <glad/glad.h>
#include <string>

class TextureArray
{
private:
    GLuint ID;
    GLenum slot;
    GLint format;

    bool is_loaded;

    int width, height, depth;
    int size;

    friend class TextureManager;

public:
    TextureArray(GLenum slot, GLint format, int width, int height, int depth);
    ~TextureArray();

    void bind();
    void unbind();

    bool is();

private:
    bool load(const std::string& path, int layers);
    void loadInitTextureArray();
    void loadLayers(unsigned char* data, int width, int height, int channels, int layers);

};