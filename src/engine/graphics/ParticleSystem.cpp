#include "ParticleSystem.h"

LittleEngine::ParticleSystem::ParticleSystem() : numParticles(1), particles(), dimensions(1., 1., 1.)
{
}

LittleEngine::ParticleSystem::~ParticleSystem()
{
	particles.clear();
	delete vao;
	delete[] this;
}

void LittleEngine::ParticleSystem::initializeVAOData(ProgramObject* program)
{
	BufferObject* particleBuffer = new BufferObject(GL_FLOAT, GL_SHADER_STORAGE_BUFFER);	

	particles.reserve(numParticles);
	particles.resize(numParticles);
	glm::vec3 goPos = gameObject->transform->position;
	for (size_t i = 0; i < numParticles; ++i)
	{
		Particle particle = Particle();
		glm::vec3 randomVector = glm::vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
		
		particle.position = glm::vec4(goPos - dimensions * .5f + dimensions * randomVector, 1);
		particle.velocity = glm::vec4(0, 2, 0, 0);
		particle.color    = glm::vec4(1, 1, 0, 1);
		particle.lifetime = glm::vec4(0);

		particles[i] = particle;
	}

	particleBuffer->addDataToShaderSpecifyDataSize(&particles[0], numParticles, sizeof(Particle))->bindBufferBase(0);
	
	vao = new BufferArrayObject();
	vao->generateVAO()->bind()->setSize(numParticles);

	particleBuffer->setBufferType(GL_ARRAY_BUFFER);

	int inPos = program->getVariableId("inPos", LittleEngine::VariableType::ATTRIBUTE);
	int inVel = program->getVariableId("inVel", LittleEngine::VariableType::ATTRIBUTE);
	int inCol = program->getVariableId("inCol", LittleEngine::VariableType::ATTRIBUTE);
	int inLif = program->getVariableId("inLif", LittleEngine::VariableType::ATTRIBUTE);	

	std::vector<AttributeVariable*> attibutes;
	attibutes.push_back(new AttributeVariable(inPos, 4, sizeof(Particle)));
	attibutes.push_back(new AttributeVariable(inVel, 4, sizeof(Particle)));
	attibutes.push_back(new AttributeVariable(inCol, 4, sizeof(Particle)));
	attibutes.push_back(new AttributeVariable(inLif, 4, sizeof(Particle)));
	vao->addBufferObject(*particleBuffer, attibutes);
}

void LittleEngine::ParticleSystem::onStart()
{
}

void LittleEngine::ParticleSystem::onUpdate(double deltaTime)
{
}

void LittleEngine::ParticleSystem::onRender(ProgramObject* program, ViewProj& viewProj)
{
	int normalLocation        = program->getVariableId("normal",        LittleEngine::VariableType::UNIFORM);
	int modelViewLocation     = program->getVariableId("modelView",     LittleEngine::VariableType::UNIFORM);
	int modelViewProjLocation = program->getVariableId("modelViewProj", LittleEngine::VariableType::UNIFORM);
	int modelLocation         = program->getVariableId("proj",          LittleEngine::VariableType::UNIFORM);
	int viewProjLocation      = program->getVariableId("viewProj",      LittleEngine::VariableType::UNIFORM);

	glm::mat4 model         = gameObject->transform->GetTransformationMatrix();
	glm::mat4 modelView     = viewProj.view * model;
	glm::mat4 normal        = glm::transpose(glm::inverse(modelView));
	glm::mat4 modelViewProj = viewProj.proj * modelView;
	glm::mat4 viewProjMat   = viewProj.proj * viewProj.view;

	if (normalLocation > -1)		program->setUniformMatrix4fv(normalLocation,        &normal[0][0]);
	if (modelViewLocation > -1)		program->setUniformMatrix4fv(modelViewLocation,     &modelView[0][0]);
	if (modelViewProjLocation > -1)	program->setUniformMatrix4fv(modelViewProjLocation, &modelViewProj[0][0]);
	if (modelLocation > -1)			program->setUniformMatrix4fv(modelLocation,         &model[0][0]);
	if (viewProjLocation > -1)		program->setUniformMatrix4fv(viewProjLocation,      &viewProjMat[0][0]);

	
	vao->bind()->render(program->getRenderMode());
}

void LittleEngine::ParticleSystem::onCompute(ProgramObject* program)
{
	vao->compute(numParticles / LITTLE_ENGINE_WORK_GROUP_SIZE);
}
