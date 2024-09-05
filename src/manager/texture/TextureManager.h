#pragma once
#include <glad/glad.h>
#include <map>
#include <memory>
#include <string>

#include "../../graphic/texture/Texture.h"
#include "../../graphic/texture/TextureArray.h"

class TextureManager {
private:
    using TextureMap = std::map<std::string, std::shared_ptr<::Texture>>;
    static TextureMap textures;

    using TextureArrayMap = std::map<std::string, std::shared_ptr<::TextureArray>>;
    static TextureArrayMap texture_arrays;

public:
    static bool Init();
    static void Terminate();

    class Texture {
    public:
        static bool load(const std::string& name, GLenum slot, GLint format, const std::string& path);
        static void unload(const std::string& name);
        static std::shared_ptr<::Texture> get(const std::string& name);

    private:
        Texture() = delete;
        ~Texture() = delete;
    };

    class TextureArray {
    public:
        static bool load(const std::string& name, GLenum slot, GLint format, int width, int height, int depth);
        static void unload(const std::string& name);
        static std::shared_ptr<::TextureArray> get(const std::string& name);

        static bool loadTexture(const std::string& name, const std::string& path, int layers);

    private:
        TextureArray() = delete;
        ~TextureArray() = delete;

        static GLint getMaxDepth();
    };

private:
    TextureManager() = delete;
    ~TextureManager() = delete;
};