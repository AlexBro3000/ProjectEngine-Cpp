#pragma once
#include <glad/glad.h>
#include <string>

class Shader
{
private:
	GLuint ID;

public:
	Shader(GLenum type, const std::string& path);
	~Shader();

	GLuint getId() const;

	bool is() const;
	
private:
	static std::string load(const std::string& path);

};