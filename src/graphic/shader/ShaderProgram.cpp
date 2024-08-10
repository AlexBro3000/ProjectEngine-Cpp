#include "ShaderProgram.h"
#include "../../graphic/shader/Shader.h"
#include "../../system/console/Console.h"

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