#pragma once
#ifndef LIGHT_H_
#define LIGHT_H_

#include "engine/scene/GameObject.h"
#include "engine/graphics/ViewProj.h"

namespace LittleEngine
{
	enum class LightType
	{
		POINT,
		DIRECTIONAL,
		SPOTLIGHT
	};
	class Light: public GameObject
	{
	private:
		LightType lightType;
		glm::vec3 intensity;
		// TODO: comment
		glm::vec3 postion;
		// TODO: comment
		glm::vec3 direction;
		float	  apertureAngle;
		float     spotlightFading;
	public:
		Light(unsigned int id, const char* name, LightType lightType = LightType::POINT);
		~Light();

		void onRender(ProgramObject* program, ViewProj& viewProj) override;
	};
}

#endif // !LIGHT_H_
