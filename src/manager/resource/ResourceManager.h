#pragma once
#include <string>

class ResourceManager
{
private:
	static std::string path;

public:
	static bool Init(int argc, char** argv);
	static void Terminate();

	friend class ShaderManager;
	friend class TextureManager;

private:
	ResourceManager() = delete;
	~ResourceManager() = delete;

	static std::string getLaunchDirectory(const std::string& path);
};