#pragma once
#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_

#define random(min, max) min + (max - min) * (float)rand() / RAND_MAX

#include <stdlib.h>
#include <vector>
#include <glm/glm.hpp>
#include "engine/utils/Clock.h"
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
		glm::vec4 initPos;
		glm::vec4 initVel;
	};

	class ParticleSystem : public IComputable, public IRenderizable
	{
	private:
		int                   numParticles;
		std::vector<Particle> particles;
		bool                  globalSpeed;
		float                 radius;
		float                 dispersion;
		float                 minLife;
		float                 maxLife;
		glm::vec3             initialSpeed;		
		glm::vec4             colorIni;
		glm::vec4             colorEnd;

		BufferObject*         particleBuffer;

		glm::vec3       squareToUniformDisk     (float a, float b);
	public:
		ParticleSystem();
		~ParticleSystem();

		inline void     setNumParticles   (int value)                          { numParticles = value; }
														                       
		inline void     setRadius         (float value)                        { radius       = value; }
		inline void     setDispersion     (float value)                        { dispersion   = value; }
		inline void     setMinLife        (float value)                        { minLife      = value; }
		inline void     setMaxLife        (float value)                        { maxLife      = value; }
		inline void     setInitialSpeed   (glm::vec3 value)                    { initialSpeed = value; }
		inline void     setSpeedAsGlobal  (bool value)                         { globalSpeed  = value; }

		inline void     setColorIni       (glm::vec4 color)                    { colorIni     = color; }
		inline void     setColorIni       (glm::vec3 color)                    { colorIni     = glm::vec4(color, 1); }
		inline void     setColorIni       (float r, float g, float b)          { colorIni     = glm::vec4(r, g, b, 1); }
		inline void     setColorIni       (float r, float g, float b, float a) { colorIni     = glm::vec4(r, g, b, a); }
									      												      
		inline void     setColorEnd       (glm::vec4 color)                    { colorEnd     = color; }
		inline void     setColorEnd       (glm::vec3 color)                    { colorEnd     = glm::vec4(color, 1); }
		inline void     setColorEnd       (float r, float g, float b)          { colorEnd     = glm::vec4(r, g, b, 1); }
		inline void     setColorEnd       (float r, float g, float b, float a) { colorEnd     = glm::vec4(r, g, b, a); }

		void			initializeVAOData (ProgramObject* program);

		void			onStart           ();
		void			onUpdate          (double deltaTime);
		void			onRender          (ProgramObject* program, ViewProj& viewProj);
		void            onCompute         (ProgramObject* program);
	};
}

#endif // !PARTICLESYSTEM_H_
