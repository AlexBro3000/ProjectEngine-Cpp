#include "TextureManager.h"
#include "../../manager/resource/ResourceManager.h"
#include "../../system/console/Console.h"

TextureManager::TextureMap TextureManager::textures;
TextureManager::TextureArrayMap TextureManager::texture_arrays;

bool TextureManager::Init()
{
    Console::Info("Initialization of the texture manager completed successfully.",
        { "Texture manager initialized." });
    return true;
}

void TextureManager::Terminate()
{
	textures.clear();
    Console::Info("Terminating the texture manager.",
        { "The texture manager has terminated." });
}

////////////////////////////////////////////////////////////////////////////////
/////     TEXTURE                                                          /////
////////////////////////////////////////////////////////////////////////////////

bool TextureManager::Texture::load(const std::string& name, const std::string& path, GLenum slot, GLint format)
{
    if (textures.find(name) != textures.end()) {
        Console::Warn("A texture with this name already exists.",
            { "Name: " + name });
        return false;
    }

    std::shared_ptr<::Texture> texture = std::make_shared<::Texture>(ResourceManager::path + path, slot, format);
    if (!texture->is()) {
        Console::Warn("Failed to load texture.",
            { "Name: " + name });
        return false;
    }
    textures[name] = texture;
    return true;
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
/////     TEXTURE ARRAY                                                    /////
////////////////////////////////////////////////////////////////////////////////

bool TextureManager::TextureArray::load(const std::string& name, GLenum slot, GLint format, GLsizei width, GLsizei height, GLsizei depth)
{
    if (texture_arrays.find(name) != texture_arrays.end()) {
        Console::Warn("A texture array with this name already exists.",
            { "Name: " + name });
        return false;
    }

    std::shared_ptr<::TextureArray> texture_array = std::make_shared<::TextureArray>(slot, format, width, height, depth);
    if (!texture_array->is()) {
        Console::Warn("Failed to load texture array.",
            { "Name: " + name });
        return false;
    }
    texture_arrays[name] = texture_array;
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

void TextureManager::TextureArray::loadTexture(const std::string& name, const std::string& path, int layers)
{
    if (texture_arrays.find(name) != texture_arrays.end()) {

        texture_arrays[name]->loadTexture(ResourceManager::path + path, layers);
    }


    





}