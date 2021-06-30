#include "ParticleAttractor.h"

LittleEngine::ParticleAttractor::ParticleAttractor() : atractors(), atractorBuffer(nullptr)
{
}

LittleEngine::ParticleAttractor::~ParticleAttractor()
{
	atractors.clear();
	delete atractorBuffer;
	delete[] this;
}

LittleEngine::ParticleAttractor* LittleEngine::ParticleAttractor::addAttractor(glm::vec3 worldPosition, float atractionIntensity, float actionRadius)
{
	Attractor atr = Attractor();
	atr.position  = glm::vec4(worldPosition, actionRadius);
	float sign    = atractionIntensity < 0 ? -1 : 1;
	atr.force     = glm::vec4(sign * atractionIntensity, sign, 0.0, 0.0);
	atractors.push_back(atr);
	return this;
}

LittleEngine::ParticleAttractor* LittleEngine::ParticleAttractor::createBufferToCompute(int computeBufferLocation)
{
	atractorBuffer = new BufferObject(GL_FLOAT, GL_SHADER_STORAGE_BUFFER);
	atractorBuffer
		->addDataToShaderSpecifyDataSize(&atractors[0], atractors.size(), sizeof(Attractor))
		->bindBufferBase(computeBufferLocation);
	return this;
}

void LittleEngine::ParticleAttractor::onStart()
{
}

void LittleEngine::ParticleAttractor::onUpdate(double deltaTime)
{
}

