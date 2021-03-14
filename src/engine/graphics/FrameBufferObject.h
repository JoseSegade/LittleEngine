#pragma once
#ifndef FRAMEBUFFEROBJECT_H_
#define FRAMEBIFFERPBJECT_H_

#include "engine\graphics\Material.h"

namespace LittleEngine
{
	class FrameBufferObject 
	{
		MeshRenderer* meshRenderer;
		Material* material;
		Mesh* mesh;
	};
}

#endif // !FRAMEBUFFEROBJECT_H_

