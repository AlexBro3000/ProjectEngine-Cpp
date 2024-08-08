#include "ResourceManager.h"
#include "../../system/console/Console.h"

std::string ResourceManager::path;

bool ResourceManager::Init(int argc, char** argv)
{
	ResourceManager::path = getLaunchDirectory(argv[0]);

	Console::Info("Initialization of the resource manager completed successfully.", {
		"Resource manager initialized.",
		"Launch directory: " + ResourceManager::path
		});
	return true;
}

void ResourceManager::Terminate()
{
	Console::Info("Terminating the resource manager.",
		{ "The resource manager has terminated." });
}

std::string ResourceManager::getLaunchDirectory(const std::string& path)
{
	size_t found = path.find_last_of("/\\");
	return path.substr(0, found);
}