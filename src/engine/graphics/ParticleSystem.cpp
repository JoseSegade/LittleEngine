#include "ParticleSystem.h"

glm::vec3 LittleEngine::ParticleSystem::squareToUniformDisk(float a, float b)
{
	float r = sqrt(a);
	float theta = 2 * 3.14159265359f * b;
	return glm::vec3(r * cos(theta), 0.f, r * sin(theta));
}

LittleEngine::ParticleSystem::ParticleSystem() :
	particleBuffer(nullptr), numParticles(1), particles(), globalSpeed(false),
	radius(1.f), dispersion(1.f), minLife(0.), maxLife(10.), initialSpeed(0, 3., 0), 
	colorIni(0.85, 0.576, 0.239, 1), colorEnd(0.421, 0.25, 0.172, 1)
{
}

LittleEngine::ParticleSystem::~ParticleSystem()
{
	particles.clear();
	delete vao;
	delete particleBuffer;
	delete[] this;
}

void LittleEngine::ParticleSystem::initializeVAOData(ProgramObject* program)
{
	particleBuffer = new BufferObject(GL_FLOAT, GL_SHADER_STORAGE_BUFFER);	

	particles.reserve(numParticles);
	particles.resize(numParticles);
	glm::mat4x4 goTransform = gameObject->transform->GetTransformationMatrix();

	for (size_t i = 0; i < numParticles; ++i)
	{
		glm::vec4 randPoint = glm::vec4(radius * squareToUniformDisk(random(0.f, 1.f), random(0.f, 1.f)), 1.f);
		glm::vec3 randSpeed = glm::vec3(
			random(-dispersion *.5, dispersion *.5),
			random(-dispersion *.5, dispersion *.5),
			random(-dispersion *.5, dispersion *.5));

		Particle particle = Particle();
		particle.position = goTransform * randPoint;
		particle.velocity = globalSpeed ? 
			glm::vec4(initialSpeed + randSpeed, 0) : 
			goTransform * glm::vec4(initialSpeed + randSpeed, 0);
		particle.color    = glm::vec4(0.f, 0.f, 0.f, 1.f);
		particle.lifetime = glm::vec4(0.f, random(minLife, maxLife), 0.f, 0.f);
		particle.initPos  = particle.position;
		particle.initVel  = particle.velocity;

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
	int inInP = program->getVariableId("inInP", LittleEngine::VariableType::ATTRIBUTE);
	int inInV = program->getVariableId("inInV", LittleEngine::VariableType::ATTRIBUTE);

	std::vector<AttributeVariable*> attibutes;
	attibutes.push_back(new AttributeVariable(inPos, 4, sizeof(Particle)));
	attibutes.push_back(new AttributeVariable(inVel, 4, sizeof(Particle)));
	attibutes.push_back(new AttributeVariable(inCol, 4, sizeof(Particle)));
	attibutes.push_back(new AttributeVariable(inLif, 4, sizeof(Particle)));
	attibutes.push_back(new AttributeVariable(inInP, 4, sizeof(Particle)));
	attibutes.push_back(new AttributeVariable(inInV, 4, sizeof(Particle)));
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
	int i_colorIni = program->getVariableId("colorIni", LittleEngine::VariableType::UNIFORM);
	int i_colorEnd = program->getVariableId("colorEnd", LittleEngine::VariableType::UNIFORM);
	if (i_colorIni > -1)		program->setUniform4fv(i_colorIni, &colorIni[0]);
	if (i_colorEnd > -1)		program->setUniform4fv(i_colorEnd, &colorEnd[0]);
	
	particleBuffer->setBufferType(GL_SHADER_STORAGE_BUFFER);
	particleBuffer->bindBufferBase(0);
	vao->compute(numParticles / LITTLE_ENGINE_WORK_GROUP_SIZE);
}