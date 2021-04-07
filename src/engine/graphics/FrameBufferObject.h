#pragma once
#ifndef FRAMEBUFFEROBJECT_H_
#define FRAMEBIFFERPBJECT_H_

#include "engine\graphics\BufferArrayObject.h"
#include "engine\graphics\Material.h"
#include "engine\components\Mesh.h"

namespace LittleEngine
{
	class FrameBufferObject : public BufferObject
	{
	private:
		Material* material;

	public:
		void setFrameVAO();
	};
}

#endif // !FRAMEBUFFEROBJECT_H_

