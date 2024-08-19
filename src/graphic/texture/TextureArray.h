#pragma once
#include <glad/glad.h>
#include <string>

class TextureArray
{
private:
    GLuint ID;
    GLenum slot;

    GLint format;
    GLsizei width, height, depth;
    GLsizei size;

    friend class TextureManager;

public:
    TextureArray(GLenum slot, GLint format, GLsizei width, GLsizei height, GLsizei depth);
    ~TextureArray();

    void bind();
    void unbind();

    bool is();

private:
    void loadTexture(const std::string& path, int layers);

};