#pragma once
#ifndef RENDERER_H_
#define RENDERER_H_

#include <glm/glm.hpp>
#include "ProgramObject.h"
#include "ViewProj.h"
#include "engine/graphics/FrameBufferObject.h"
#include "engine/graphics/ProgramObject.h"

namespace LittleEngine 
{
	enum class WireframeType
	{
		POINT,
		LINE
	};
	class Renderer 
	{
	private:
		glm::vec4			bgColor;
		FrameBufferObject*	fbo;
	public: 
		Renderer();
		~Renderer();

		void		renderFBO					(ProgramObject* programObject);
		Renderer*	createFBO					(ProgramObject* programObject);
		Renderer*	changeBackgroungColor		(glm::vec4 color);
		Renderer*	startRenderConfig			();
		Renderer*	clearBuffersFw				();
		Renderer*	clearBuffersPP				();
		Renderer*	resize						(int width, int height);
		Renderer*	uploadTimeToProgram			(ProgramObject* program, double deltaTime);
		Renderer*	uploadResolutionToProgram	(ProgramObject* program, unsigned int widht, unsigned int height);
		Renderer*	setWireframeWidth			(float width, WireframeType type = WireframeType::LINE);
		template<typename T>
		Renderer*	uploadUniformVariable		(ProgramObject* program, const char* name, T* value);
	};
	template<typename T>
	Renderer* LittleEngine::Renderer::uploadUniformVariable(ProgramObject* program, const char* name, T* value)
	{
		int location = program->getVariableId(name, VariableType::UNIFORM);
		if (location < 0) return this;

		if (typeid(T) == typeid(float))
		{
			float* val = reinterpret_cast<float*>(value);
			program->setUniform1f(location, *val);
		}
		else if (typeid(T) == typeid(double))
		{
			double* val = reinterpret_cast<double*>(value);
			program->setUniform1d(location, *val);
		}
		else if (typeid(T) == typeid(unsigned int))
		{
			unsigned int* val = reinterpret_cast<unsigned int*>(value);
			program->setUniform1u(location, *val);
		}
		else if (typeid(T) == typeid(int))
		{
			int* val = reinterpret_cast<int*>(value);
			program->setUniform1i(location, *val);
		}
		else if (typeid(T) == typeid(glm::mat4))
		{
			glm::mat4* mat = reinterpret_cast<glm::mat4*>(value);
			program->setUniformMatrix4fv(location, &mat[0][0][0]);
		}
		else if (typeid(T) == typeid(glm::vec3))
		{
			glm::vec3* vec = reinterpret_cast<glm::vec3*>(value);
			program->setUniform3fv(location, &vec[0][0]);
		}
		else if (typeid(T) == typeid(glm::vec4))
		{
			glm::vec4* vec = reinterpret_cast<glm::vec4*>(value);
			program->setUniform4fv(location, &vec[0][0]);
		}
		else
		{
			Utils::printWarning("This variable type is not implemented yet.", __FILE__, __LINE__);
		}
		return this;
	}
}

#endif // !RENDERER_H_

