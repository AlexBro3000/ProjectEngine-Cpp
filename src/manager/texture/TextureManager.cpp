#include "TextureManager.h"
#include "../../manager/resource/ResourceManager.h"
#include "../../system/console/Console.h"

TextureManager::TextureMap TextureManager::textures;

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

bool TextureManager::Texture::load(const std::string& name, const std::string& path, GLenum slot, GLint format, GLenum pxl_format, GLenum pxl_type)
{
    if (textures.find(name) != textures.end()) {
        Console::Warn("A texture with this name already exists.",
            { "Name: " + name });
        return false;
    }

    std::shared_ptr<::Texture> texture = std::make_shared<::Texture>(ResourceManager::path + path, slot, format, pxl_format, pxl_type);
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