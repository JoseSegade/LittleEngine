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
		Material*			material;
	public:
		MeshRenderer(): Component(), vao(nullptr), indexBuffer(nullptr), mesh(nullptr), material(nullptr) {}
		~MeshRenderer();

		inline void		setMesh				(Mesh* value)		{ mesh = value; }
		inline void		setMaterial			(Material* value)	{ material = value; }

		void			initializeVAOData	(ProgramObject* program);

		void			onStart				();
		void			onUpdate			(double deltaTime);
		void			onRender			(ProgramObject* program, ViewProj &viewProj);
	};
}

#endif // !MESHRENDERER_H_
