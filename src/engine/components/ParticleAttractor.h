#pragma once
#ifndef PARTICLEATTRACTOR_H_
#define PARTICLEATTRACTOR_H_

#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include "engine/graphics/BufferObject.h"
#include "engine/components/Component.h"

namespace LittleEngine
{
	struct Attractor
	{
		glm::vec4 position;
		glm::vec4 force;
	};

	class ParticleAttractor: public Component
	{
	private:
		std::vector<Attractor> atractors;
		BufferObject* atractorBuffer;
	public:
		ParticleAttractor();
		~ParticleAttractor();

		ParticleAttractor* addAttractor           (glm::vec3 worldPosition, float atractionIntensity, float actionRadius);
		ParticleAttractor* createBufferToCompute (int computeBufferLocation);

		void onStart                            ();
		void onUpdate                           (double deltaTime);
	};
}

#endif // !PARTICLEATRACTOR_H_

