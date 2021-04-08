#include "Light.h"

LittleEngine::Light::Light(unsigned int id, const char* name, LightType lightType): GameObject(id, name), lightType(lightType)
{
}

LittleEngine::Light::~Light()
{
	delete[] this;
}

void LittleEngine::Light::onRender(ProgramObject* program, ViewProj& viewProj)
{

}
