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
	enum class RenderMode {
		TRIANGLES,
		QUADS,
		TRIANGLES_PATCH,
		POINTS
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

		RenderMode											renderMode;

		void searchForAttributes	();
		void searchForUniforms		();
		void searchAndStoreVariables(VariableType type);
	public:
		ProgramObject(const char* name, RenderMode renderMode = RenderMode::TRIANGLES);
		~ProgramObject();
		
		inline RenderMode getRenderMode() { return renderMode; }

		ProgramObject*	addShader			(Shader* shader);
		ProgramObject*	loadProgram			();
		ProgramObject*	use					();
		ProgramObject*	setUniform1u		(unsigned int variableLocation, int value);
		ProgramObject*	setUniform1i		(unsigned int variableLocation, int index);
		ProgramObject*	setUniform1f		(unsigned int variableLocation, float value);
		ProgramObject*	setUniform1d		(unsigned int variableLocation, double value);
		ProgramObject*	setUniformMatrix4fv	(unsigned int variableLocation, const float* values);
		ProgramObject*  setUniform3fv       (unsigned int variableLocation, const float* values);
		ProgramObject*	setUniform4fv		(unsigned int variableLocation, const float* values);
		int				getVariableId		(const std::string& name, const VariableType& type);		
	};
}

#endif // !PROGRAMOBJECT_H_

