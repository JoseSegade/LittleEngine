#pragma once
#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H_

#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include "ISingleton.h"
#include "engine\graphics\Shader.h"
#include "engine\graphics\ProgramObject.h"

namespace LittleEngine
{
	class ShaderManager: public ISingleton<ShaderManager>
	{
	private:
		std::unordered_map<std::string, Shader*>			shaders;
		std::unordered_map<std::string, ProgramObject*>		programs;
	public:
		ShaderManager* createProgram	(const char* programName);
		ShaderManager* createShader		(const char* shaderName, const char* shaderPath, GLenum type);
		ShaderManager* assignShader		(const char* shaderName, const char* programName);
		ShaderManager* loadAllPrograms	();
		ShaderManager* loadProgram		(const char* programName);
		ShaderManager* useProgram		(const char* programName);

		ProgramObject*	getProgram		(const char* programName);
		Shader*			getShader		(const char* shaderName);
		Shader*			getShader		(const char* shaderName);
	};
}

#endif // !SHADER_MANAGER
