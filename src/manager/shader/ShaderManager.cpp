#include "ShaderManager.h"

#include "../../manager/resource/ResourceManager.h"
#include "../../system/console/Console.h"

ShaderManager::ShaderProgramMap ShaderManager::shader_programs;

bool ShaderManager::Init()
{
	Console::Info("Shader manager (Init)", {
		"Initialization of the shader manager completed successfully."
		});
	return true;
}

void ShaderManager::Terminate()
{
	shader_programs.clear();

	Console::Info("Shader manager (Terminate)", {
		"Terminating the shader manager completed successfully."
		});
}

////////////////////////////////////////////////////////////////////////////////
/////     SHADER MANAGER :: SHADER PROGRAM                                 /////
////////////////////////////////////////////////////////////////////////////////

bool ShaderManager::ShaderProgram::load(const std::string& name, const std::string& path_vert, const std::string& path_frag)
{
	if (shader_programs.find(name) != shader_programs.end()) {
		Console::Warn("Shader manager", { "A shader program with this name already exists.", "Name: " + name });
		return false;
	}

	std::shared_ptr<::ShaderProgram> shader = std::make_shared<::ShaderProgram>();
	bool flag = shader->load(ResourceManager::path + path_vert, ResourceManager::path + path_frag);

	if (flag && shader->is()) {
		shader_programs[name] = shader;
		Console::Info("Shader manager", { "Shader program loaded successfully.", "Name: " + name });
		return true;
	}
	else {
		Console::Warn("Shader manager", { "Failed to load shader program.", "Name: " + name });
		return false;
	}
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