#include "Shader.h"
#include "../../system/console/Console.h"
#include <fstream>
#include <sstream>

Shader::Shader(GLenum type, const std::string& path) :
	ID(0)
{
	std::string shader_code_str = Shader::load(path);
	const GLchar* shader_code = shader_code_str.c_str();

	ID = glCreateShader(type);
	glShaderSource(ID, 1, &shader_code, nullptr);
	glCompileShader(ID);

	GLint success;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar info_log[512];
		glGetShaderInfoLog(ID, 512, nullptr, info_log);
		glDeleteShader(ID);

		Console::Warn("Failed to compile shader.", {
			"Path: " + path,
			info_log });
	}
}

Shader::~Shader()
{
	if (Shader::is()) {
		glDeleteShader(ID);
	}
}

GLuint Shader::getId() const
{
	return ID;
}

bool Shader::is() const
{
	return (ID != 0) && glIsShader(ID);
}

std::string Shader::load(const std::string& path)
{
	std::string shader_code = std::string();
	try {
		std::ifstream shader_file(path);
		shader_file.exceptions(std::ifstream::badbit);
		if (shader_file.is_open()) {
			std::stringstream shader_stream;
			shader_stream << shader_file.rdbuf();
			shader_code = shader_stream.str();
			Console::Info("The shader file was read successfully.",
				{ "Path: " + path });
		}
		else {
			Console::Warn("Failed to open shader file.",
				{ "Path: " + path });
		}
	}
	catch (std::ifstream::failure& exc) {
		Console::Warn("Failed to read shader file.",
			{ "Path: " + path });
	}
	return shader_code;
}