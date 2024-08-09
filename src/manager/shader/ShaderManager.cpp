#include "ShaderManager.h"
#include "../../manager/resource/ResourceManager.h"
#include "../../system/console/Console.h"

ShaderManager::ShaderProgramMap ShaderManager::shader_programs;

bool ShaderManager::Init()
{
	Console::Info("Initialization of the shader manager completed successfully.",
		{ "Shader manager initialized." });
	return true;
}

void ShaderManager::Terminate()
{
	shader_programs.clear();
	Console::Info("Terminating the shader manager.",
		{ "The shader manager has terminated." });
}

////////////////////////////////////////////////////////////////////////////////
/////     SHADER PROGRAM                                                   /////
////////////////////////////////////////////////////////////////////////////////

bool ShaderManager::ShaderProgram::load(const std::string& name, const std::string& path_vert, const std::string& path_frag)
{
	if (shader_programs.find(name) != shader_programs.end()) {
		Console::Warn("A shader program with this name already exists.",
			{ "Name: " + name });
		return false;
	}

	std::shared_ptr<::ShaderProgram> shader = std::make_shared<::ShaderProgram>(ResourceManager::path + path_vert, ResourceManager::path + path_frag);
	if (!shader->is()) {
		Console::Warn("Failed to load shader program.",
			{ "Name: " + name });
		return false;
	}
	shader_programs[name] = shader;
	return true;
}

void ShaderManager::ShaderProgram::unload(const std::string& name)
{
	if (shader_programs.find(name) != shader_programs.end()) {
		shader_programs.erase(name);
	}
}

std::shared_ptr<::ShaderProgram> ShaderManager::ShaderProgram::get(const std::string& name)
{
	return shader_programs.at(name);
}