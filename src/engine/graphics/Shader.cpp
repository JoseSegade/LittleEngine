#include "Shader.h"
#include <iostream>

LittleEngine::Shader::Shader(const std::string& name, GLenum type): name(name), program(0), type(type)
{
}

LittleEngine::Shader::~Shader()
{
	this->attributes.clear();
	this->uniforms.clear();
}

void LittleEngine::Shader::SearchForAttributes()
{
}

void LittleEngine::Shader::SearchForUniforms()
{
}

void LittleEngine::Shader::SearchAndStoreVariables(LittleEngine::VariableType type)
{

}

std::string LittleEngine::Shader::GetName()
{
	return this->name;
}

int LittleEngine::Shader::GetProgram()
{
	return this->program;
}

GLenum LittleEngine::Shader::GetType()
{
	return this->type;
}

void LittleEngine::Shader::Bind()
{
	glUseProgram(this->program);
}

void LittleEngine::Shader::Unbind()
{
	glUseProgram(0);
}

GLuint LittleEngine::Shader::LoadShader(const char* fileName)
{
	unsigned int fileLen;
	//char* source = loadStringFromFile(fileName, fileLen);
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &fileName, 0);
	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		char* logString = new char[maxLength];
		glGetShaderInfoLog(shader, maxLength, &maxLength, logString);
		std::cout << "Error: " << logString << std::endl;
		delete[] logString;
		glDeleteShader(shader);
		return -1;
	}
	return shader;
}

int LittleEngine::Shader::GetVariableId(const std::string& name, const VariableType& type)
{
	return 0;
}
