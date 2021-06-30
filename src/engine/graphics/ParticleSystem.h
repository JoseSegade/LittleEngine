#pragma once
#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_

#include <stdlib.h>
#include <vector>
#include <glm/glm.hpp>
#include "engine/graphics/IComputable.h"
#include "engine/graphics/IRenderizable.h"
#include "engine/graphics/ProgramObject.h"

namespace LittleEngine
{
	struct Particle
	{
		glm::vec4 position;
		glm::vec4 velocity;
		glm::vec4 color;
		glm::vec4 lifetime;
	};

	class ParticleSystem : public IComputable, public IRenderizable
	{
	private:
		int                   numParticles;
		std::vector<Particle> particles;
		glm::vec3             dimensions;
	public:
		ParticleSystem();
		~ParticleSystem();

		inline void     setNumParticles   (int value) { numParticles = value; }

		void			initializeVAOData (ProgramObject* program);

		void			onStart           ();
		void			onUpdate          (double deltaTime);
		void			onRender          (ProgramObject* program, ViewProj& viewProj);
		void            onCompute         (ProgramObject* program);
	};
}

#endif // !PARTICLESYSTEM_H_
