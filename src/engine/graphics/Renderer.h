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
	class Renderer 
	{
	private:
		glm::vec4			bgColor;
		FrameBufferObject*	fbo;
	public: 
		Renderer();
		~Renderer();

		void		renderFBO								(ProgramObject* programObject);
		Renderer*	createFBO								(ProgramObject* programObject);
		Renderer*	changeBackgroungColor					(glm::vec4 color);
		Renderer*	startRenderConfig						();
		Renderer*	clearBuffersFw							();
		Renderer*	clearBuffersPP							();
		Renderer*	resize									(int width, int height);
		Renderer*	uploadTimeToProgram						(ProgramObject* program, double deltaTime);
		Renderer*	uploadResolutionToProgram				(ProgramObject* program, unsigned int widht, unsigned int height);
	};
}

#endif // !RENDERER_H_

