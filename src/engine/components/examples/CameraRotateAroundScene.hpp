#pragma once
#ifndef CAMERAROTATEAROUNDSCENE_H_
#define CAMERAROTATEAROUNDSCENE_H_

#include <functional>
#include <glm/glm.hpp>
#include "engine/managers/InputManager.h"
#include "engine/scene/GameObject.h"

class CameraRotateAroundScene : public LittleEngine::Component
{
private:
	glm::vec2 lastPos;
	glm::vec2 screenPos;
	float delta;
	bool isPressed;
	float speed;
	glm::vec3 zoomAngle;

	int zoomTimes;

public:
	inline void setSpeed(float value) { speed = value; }

	void onStart()
	{
		zoomAngle = glm::normalize(glm::vec3(0.f, -8.f, -10.f));
		lastPos = glm::vec2(-1.f, -1.f);
		delta = 0.f;
		isPressed = false;
		speed = 2.f;
		zoomTimes = 0;
		std::function<void(const void*, const size_t)> f = [=](const void* data, const size_t classId) {
			this->inputHandle(data, classId);
		};

		LittleEngine::InputManager::instance()->subscribe("CAMERA_ROTATE_AROUND_SCENE", f);
	}

	void onUpdate(double deltaTime)
	{		

		if (isPressed)
		{
			gameObject->transform->rotation = glm::rotate(
				gameObject->transform->rotation, 
				glm::radians(screenPos.x - lastPos.x), 
				glm::vec3(0.f, 1., 0.f));

			lastPos = screenPos;
		}
	}

	void inputHandle(const void* data, const size_t classId)
	{
		if (classId == typeid(LittleEngine::KeyMessage).hash_code())
		{
			const LittleEngine::KeyMessage* key = reinterpret_cast<const LittleEngine::KeyMessage*>(data);

			int keyCode = key->k;

			glm::vec3 posRotatedZ = glm::toMat4(gameObject->transform->rotation) * glm::vec4(0, 0, 1, 0);
			glm::vec3 posRotatedX = glm::toMat4(gameObject->transform->rotation) * glm::vec4(1, 0, 0, 0);

			if (keyCode == 87) // 'W'
			{
				gameObject->transform->position -= posRotatedZ;
			}
			if (keyCode == 83) // 'S'
			{
				gameObject->transform->position += posRotatedZ;
			}
			if (keyCode == 68) // 'D'
			{
				gameObject->transform->position += posRotatedX;
			}
			if (keyCode == 65) // 'A'
			{
				gameObject->transform->position -= posRotatedX;
			}

		}
		if (classId == typeid(LittleEngine::MouseMessage).hash_code())
		{
			const LittleEngine::MouseMessage* mouseMessage = reinterpret_cast<const LittleEngine::MouseMessage*>(data);
			bool isCentralButton = mouseMessage->button == 2;

			if (isCentralButton)
			{
				bool isPressingNow   = mouseMessage->action == 1;
				if (!isPressed && isPressingNow)
				{
					isPressed = true;
					screenPos = glm::vec2(mouseMessage->posX, mouseMessage->posY);
					lastPos   = screenPos;
				}

				if (isPressed && !isPressingNow)
				{
					isPressed = false;
					screenPos = glm::vec2(mouseMessage->posX, mouseMessage->posY);
				}
			}
		}

		if (isPressed && classId == typeid(LittleEngine::MouseMoveMessage).hash_code())
		{
			const LittleEngine::MouseMoveMessage* mouseMessage = reinterpret_cast<const LittleEngine::MouseMoveMessage*>(data);
			screenPos = glm::vec2(mouseMessage->posX, mouseMessage->posY);
		}
	}
};

#endif // !CAMERAROTATEAROUNDSCENE_H_
