#pragma once
#ifndef FRAMEBUFFEROBJECT_H_
#define FRAMEBIFFERPBJECT_H_

#include <vector>
#include "engine/graphics/BufferArrayObject.h"
#include "engine/graphics/Material.h"
#include "engine/components/Mesh.h"
#include "engine/utils/PlaneFBO.h"

namespace LittleEngine
{
	class FrameBufferObject : public BufferObject
	{
	private:
		unsigned int planeVAOid;
		unsigned int planeVBOid;
		unsigned int colorBufferTextureId;
		unsigned int depthBufferTextureId;
		unsigned int positionBufferTextureId;
		int			 colorTextureLocation;
		int			 positionTextureLocation;
	public:
		~FrameBufferObject();

		FrameBufferObject*	setColorTextureLocation		(const int value);
		FrameBufferObject*	setPositionTextureLocation	(const int value);
		FrameBufferObject*	setFrameVAO					();
		FrameBufferObject*	generate					();
		FrameBufferObject*	resize						(unsigned int width, unsigned int height);
		FrameBufferObject*	bind						() override;
		FrameBufferObject*	unbind						() override;
		void				render						(ProgramObject* program);
	};
}

#endif // !FRAMEBUFFEROBJECT_H_

