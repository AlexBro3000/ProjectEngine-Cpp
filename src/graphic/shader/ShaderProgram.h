#pragma once
#include <glad/glad.h>
#include <string>

class ShaderProgram
{
private:
	GLuint ID;

public:
	ShaderProgram(const std::string& path_vert, const std::string& path_frag);
	~ShaderProgram();

	template<typename T>
	void setUniform(const std::string& name, const T& value) const;

	void use() const;

	bool is() const;

private:
	GLint getUniformLocation(const std::string& name) const;

};

#include "ShaderProgram.inl"