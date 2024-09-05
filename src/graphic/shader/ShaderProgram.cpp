#include "ShaderProgram.h"

#include "../../graphic/shader/Shader.h"
#include "../../system/console/Console.h"

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

bool ShaderProgram::load(const std::string& path_vert, const std::string& path_frag)
{
	if (ShaderProgram::is()) {
		Console::Warn("Shader program already loaded.", {
			"Path (Vertex shader):   " + path_vert,
			"Path (Fragment shader): " + path_frag
			});
		return false;
	}

	Shader VS = Shader(GL_VERTEX_SHADER, path_vert);
	Shader FS = Shader(GL_FRAGMENT_SHADER, path_frag);

	if (VS.is() && FS.is()) {
		ID = glCreateProgram();
		glAttachShader(ID, VS.getId());
		glAttachShader(ID, FS.getId());
		glLinkProgram(ID);

		GLint success;
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			GLchar info_log[512];
			glGetProgramInfoLog(ID, 512, nullptr, info_log);
			glDeleteProgram(ID);

			Console::Warn("Failed to link shader program.", {
				"Path (Vertex shader):   " + path_vert,
				"Path (Fragment shader): " + path_frag,
				info_log });
			return false;
		}
		return true;
	}
	return false;
}

GLint ShaderProgram::getUniformLocation(const std::string& name) const
{
	return glGetUniformLocation(ID, name.c_str());
}