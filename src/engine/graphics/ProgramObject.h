#pragma once
#ifndef PROGRAMOBJECT_H_
#define PROGRAMOBJECT_H_

#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include "engine/utils/Logger.h"
#include "Shader.h"
#include "ShaderVariable.h"

namespace LittleEngine 
{
	enum class VariableType {
		UNIFORM,
		ATTRIBUTE
	};
	enum class ProgramState {
		UNLOADED,
		LOADED
	};
	class ProgramObject 
	{
	private:
		unsigned int										id;
		std::string											name;
		ProgramState										state;
		std::unordered_map<std::string, int>				attributes;
		std::unordered_map<std::string, int>				uniforms;
		std::unordered_map<unsigned int, Shader*>			shaders;

		void searchForAttributes();
		void searchForUniforms();
		void searchAndStoreVariables(VariableType type);
	public:
		ProgramObject(const char* name);
		~ProgramObject();
		
		ProgramObject* addShader		(Shader* shader);
		ProgramObject* loadProgram		();
		ProgramObject* use				();
		int	getVariableId				(const std::string& name, const VariableType& type);		
	};
}

#endif // !PROGRAMOBJECT_H_

