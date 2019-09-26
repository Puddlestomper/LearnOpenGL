#pragma once

#include <glad/glad.h>

#include <string>

class Shader
{
public:
	//Program ID
	unsigned int ID;

	//Read and builds shaders
	Shader(const char* vertexPath, const char* fragmentPath);

	//Use/Activate Shader
	void Use();

	//Uniform methods
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
private:
	void checkCompileErrors(unsigned int shader, std::string type) const;
};