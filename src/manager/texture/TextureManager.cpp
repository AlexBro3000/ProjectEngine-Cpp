#include "TextureManager.h"

#include "../../manager/resource/ResourceManager.h"
#include "../../system/console/Console.h"

TextureManager::TextureMap TextureManager::textures;
TextureManager::TextureArrayMap TextureManager::texture_arrays;

bool TextureManager::Init()
{
    Console::Info("Texture manager (Init)", {
        "Initialization of the texture manager completed successfully."
        });
    return true;
}

void TextureManager::Terminate()
{
	textures.clear();
    texture_arrays.clear();

    Console::Info("Texture manager (Terminate)", {
        "Terminating the texture manager completed successfully."
        });
}

////////////////////////////////////////////////////////////////////////////////
/////     TEXTURE MAMAGER :: TEXTURE                                       /////
////////////////////////////////////////////////////////////////////////////////

bool TextureManager::Texture::load(const std::string& name, GLenum slot, GLint format, const std::string& path)
{
    if (textures.find(name) != textures.end()) {
        Console::Warn("Texture manager", { "A texture with this name already exists.", "Name: " + name });
        return false;
    }

    std::shared_ptr<::Texture> texture = std::make_shared<::Texture>(slot, format);
    bool flag = texture->load(ResourceManager::path + path);

    if (flag && texture->is()) {
        textures[name] = texture;
        Console::Info("Texture manager", { "Texture loaded successfully.", "Name: " + name });
        return true;
    }
    else {
        Console::Warn("Texture manager", { "Failed to load texture.", "Name: " + name });
        return false;
    }
}

void TextureManager::Texture::unload(const std::string& name)
{
    if (textures.find(name) != textures.end()) {
        textures.erase(name);
    }
}

std::shared_ptr<::Texture> TextureManager::Texture::get(const std::string& name)
{
    return textures.at(name);
}

////////////////////////////////////////////////////////////////////////////////
/////     TEXTURE MAMAGER :: TEXTURE ARRAY                                 /////
////////////////////////////////////////////////////////////////////////////////

bool TextureManager::TextureArray::load(const std::string& name, GLenum slot, GLint format, int width, int height, int depth)
{
    if (texture_arrays.find(name) != texture_arrays.end()) {
        Console::Warn("Texture manager", { "A texture array with this name already exists.", "Name: " + name });
        return false;
    }

    GLint max_layers = TextureManager::TextureArray::getMaxDepth();
    if (depth > max_layers) {
        Console::Warn("Texture manager", {
            "The number of layers exceeds the maximum available. The maximum number of layers will be used.",
            "Name:   " + name,
            "Layers: " + std::to_string(depth) + " >> " + std::to_string(max_layers)
            });
        depth = max_layers;
    }

    texture_arrays[name] = std::make_shared<::TextureArray>(slot, format, width, height, depth);
    return true;
}

void TextureManager::TextureArray::unload(const std::string& name)
{
    if (texture_arrays.find(name) != texture_arrays.end()) {
        texture_arrays.erase(name);
    }
}

std::shared_ptr<::TextureArray> TextureManager::TextureArray::get(const std::string& name)
{
    return texture_arrays.at(name);
}

bool TextureManager::TextureArray::loadTexture(const std::string& name, const std::string& path, int layers)
{
    if (texture_arrays.find(name) != texture_arrays.end()) {
        bool flag = texture_arrays[name]->load(ResourceManager::path + path, layers);

        if (flag && texture_arrays[name]->is()) {
            Console::Info("Texture manager", { "Texture array loaded successfully.", "Name: " + name });
            return true;
        }
        else {
            Console::Warn("Texture manager", { "Failed to load texture array.", "Name: " + name });
            return false;
        }
    }
    Console::Warn("Texture manager", { "Failed to load texture array. A texture array with that name does not exist.", "Name: " + name });
    return false;
}

GLint TextureManager::TextureArray::getMaxDepth()
{
    GLint max_layers;
    glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &max_layers);
    return max_layers;
}