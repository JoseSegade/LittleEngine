#include "Shader.h"

LittleEngine::Shader::Shader(const std::string& name, GLenum type): name(name), program(0), type(type), id(0)
{
}

LittleEngine::Shader::~Shader()
{
	glDeleteShader(id);
}

std::string LittleEngine::Shader::GetName()
{
	return name;
}

int LittleEngine::Shader::GetId()
{
	return id;
}

unsigned int LittleEngine::Shader::GetProgram()
{
	return *program;
}

LittleEngine::Shader* LittleEngine::Shader::SetProgram(unsigned int* value)
{
	program = value;
	return this;	
}

GLenum LittleEngine::Shader::GetType()
{
	return type;
}

LittleEngine::Shader* LittleEngine::Shader::Bind()
{
	glUseProgram(*program);
	return this;
}

LittleEngine::Shader* LittleEngine::Shader::Unbind()
{
	glUseProgram(0);
	return this;
}

GLuint LittleEngine::Shader::LoadShader(const char* fileName)
{
	unsigned int fileLen;
	char* source = LittleEngine::Utils::stringFromFile(fileName, fileLen);
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, (const GLchar **)&source, (const GLint*)&fileLen);
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
	id = shader;
	return shader;
}


