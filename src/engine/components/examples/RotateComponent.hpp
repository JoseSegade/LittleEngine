#pragma once
#ifndef ROTATECOMPONENT_H_
#define ROTATECOMPONENT_H_

#include "engine/components/Component.h"

class RotateComponent : public LittleEngine::Component
{
private:
	float angle;
public:

	void onStart() {
		angle = 0.5f;
	}

	void onUpdate(double deltaTime) {
		gameObject->transform->rotation = glm::rotate(gameObject->transform->rotation, angle * (float)deltaTime, glm::vec3(0.f, 1.f, 0.f));
	}
};

#endif // !ROTATECOMPONENT_H_

