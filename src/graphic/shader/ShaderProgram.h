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

	void use() const;

	bool is() const;

private:
};