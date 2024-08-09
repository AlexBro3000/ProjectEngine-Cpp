#pragma once
#include "../../graphic/texture/Texture.h"
#include <glad/glad.h>
#include <map>
#include <memory>
#include <string>

class TextureManager
{
private:
    using TextureMap = std::map<std::string, std::shared_ptr<::Texture>>;
    static TextureMap textures;

    friend class Texture;

public:
    static bool Init();
    static void Terminate();

    class Texture
    {
    public:
        static bool load(const std::string& name, const std::string& path, GLenum slot, GLint format, GLenum pxl_format, GLenum pxl_type);
        static void unload(const std::string& name);
        static std::shared_ptr<::Texture> get(const std::string& name);

    private:
        Texture() = delete;
        ~Texture() = delete;
    };

private:
    TextureManager() = delete;
    ~TextureManager() = delete;
};