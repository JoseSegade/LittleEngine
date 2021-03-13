#pragma once
#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <vector>
#include <glad/glad.h>
#include <iostream>
#include "engine/utils/FileReader.h"

namespace LittleEngine {
	class Shader
	{
	private:
		std::string								name;
		int										id;
		unsigned int*							program;
		GLenum									type;

	public:
		Shader(const std::string& name, GLenum type);
		~Shader();

		std::string		GetName();
		int				GetId();
		unsigned int	GetProgram();
		Shader*			SetProgram(unsigned int* value);
		GLenum			GetType();

		Shader*			Bind();
		Shader*			Unbind();

		GLuint			LoadShader		(const char* fileName);
	};
}

#endif // !SHADER_H_