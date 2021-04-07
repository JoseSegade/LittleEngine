#pragma once
#ifndef MESHRENDERER_H_
#define MESHRENDERER_H_

#include <vector>
#include "engine/components/Component.h"
#include "engine/graphics/BufferArrayObject.h"
#include "engine/components/Mesh.h"
#include "engine/graphics/Renderer.h"

namespace LittleEngine
{
	class MeshRenderer : public Component
	{
	private:
		BufferArrayObject*	vao;
		BufferObject*		indexBuffer;
		Mesh*				mesh;
	public:
		MeshRenderer();
		~MeshRenderer();

		inline void		setMesh				(Mesh* value) { mesh = value; }

		void			initializeVAOData	(ProgramObject* program);

		void			onStart				();
		void			onUpdate			(double deltaTime);
		void			render				(Renderer* renderer);
	};
}

#endif // !MESHRENDERER_H_
