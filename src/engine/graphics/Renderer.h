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
		Renderer*	createFBO								();
		Renderer*	changeBackgroungColor					(glm::vec4 color);
		Renderer*	startRenderConfig						();
		Renderer*	clearBuffersFw							();
		Renderer*	clearBuffersPP							();
		Renderer*	resize									(int width, int height);
		Renderer*	uploadTimeToProgram						(ProgramObject* program);
		Renderer*	uploadResolutionToProgram				(ProgramObject* program);
	};
}

#endif // !RENDERER_H_

