#include "ShaderProgram.h"
#include "../../system/console/Console.h"
#include <fstream>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
/////   SHADER                                                             /////
////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
/////   SHADER PROGRAM                                                     /////
////////////////////////////////////////////////////////////////////////////////

ShaderProgram::ShaderProgram(const std::string& path_vert, const std::string& path_frag) :
	ID(0)
{
	Shader VS = Shader(GL_VERTEX_SHADER, path_vert);
	Shader FS = Shader(GL_FRAGMENT_SHADER, path_frag);

	if (VS.is() && FS.is()) {
		GLuint shader_program = glCreateProgram();
		glAttachShader(shader_program, VS.getId());
		glAttachShader(shader_program, FS.getId());
		glLinkProgram(shader_program);

		GLint success;
		glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
		if (success) {
			if (ID) {
				glDeleteProgram(ID);
			}
			ID = shader_program;
		}
		else {
			GLchar info_log[512];
			glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
			glDeleteProgram(shader_program);

			Console::Warn("Failed to link shader program.", {
				"Vertex shader, Path:   " + path_vert,
				"Fragment shader, Path: " + path_frag,
				info_log });
		}
	}
}

ShaderProgram::~ShaderProgram()
{
	if (ShaderProgram::is()) {
		glDeleteProgram(ID);
	}
}

void ShaderProgram::use() const
{
	glUseProgram(ID);
}

bool ShaderProgram::is() const
{
	return (ID != 0) && glIsProgram(ID);
}