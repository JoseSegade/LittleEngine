#pragma once
#ifndef IRENDERIZABLE_H_
#define IRENDERIZABLE_H_

#include "engine/scene/GameObject.h"
#include "engine/graphics/BufferArrayObject.h"
#include "engine/graphics/ViewProj.h"

namespace LittleEngine
{
	class GameObject;
	class IRenderizable : virtual public Component
	{
	protected:
		BufferArrayObject* vao;
	public:
		virtual void initializeVAOData (ProgramObject* program)                     = 0;
		virtual void onRender          (ProgramObject* program, ViewProj& viewProj) = 0;
	};
}

#endif // !IRENDERIZABLE_H_

