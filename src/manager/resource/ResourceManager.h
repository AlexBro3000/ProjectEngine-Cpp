#pragma once
#include <string>

class ResourceManager {
private:
	static std::string path;

	friend class ShaderManager;
	friend class TextureManager;

public:
	static bool Init(int argc, char** argv);
	static void Terminate();

private:
	ResourceManager() = delete;
	~ResourceManager() = delete;

	static std::string getLaunchDirectory(const std::string& path);

};