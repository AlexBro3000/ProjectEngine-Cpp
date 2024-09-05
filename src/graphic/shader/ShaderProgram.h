#pragma once
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class ShaderProgram {
private:
	GLuint ID;

	friend class ShaderManager;

public:
	ShaderProgram() : ID(0) {}
	~ShaderProgram();

	template<typename T>
	void setUniform(const std::string& name, const T& value) const;

	void use() const;

	bool is() const;

private:
	bool load(const std::string& path_vert, const std::string& path_frag);

	GLint getUniformLocation(const std::string& name) const;

};



template<typename T>
void ShaderProgram::setUniform(const std::string& name, const T& value) const
{
	GLint location = getUniformLocation(name);
	if (location != -1) {
		if constexpr (std::is_same_v<T, float>) {
			glUniform1f(location, value);
		}
		else if constexpr (std::is_same_v<T, int>) {
			glUniform1i(location, value);
		}
		else if constexpr (std::is_same_v<T, glm::vec3>) {
			glUniform3fv(location, 1, glm::value_ptr(value));
		}
		else if constexpr (std::is_same_v<T, glm::mat4>) {
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}
	}
}