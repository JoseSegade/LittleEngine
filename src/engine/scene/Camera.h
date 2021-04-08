#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include "engine/scene/GameObject.h"

namespace LittleEngine
{
	enum class CameraProjection 
	{
		PERSPECTIVE,
		ORTOGRAPHIC
	};
	class Camera : public GameObject
	{
	private:
		glm::mat4			projMat;
		unsigned int		width;
		unsigned int		height;
		CameraProjection	cameraProjection;
		float				nearClip;
		float				farClip;
		float				fov;

	public:
		Camera(unsigned int id, const char* name, CameraProjection cameraProjection);
		Camera(unsigned int id, const char* name, Transform* t, CameraProjection cameraProjection);
		~Camera();

		inline CameraProjection getCameraProjection	() const { return cameraProjection; }
		inline ViewProj			getViewProj			() const { return ViewProj(glm::inverse(transform->GetTransformationMatrix()), projMat); }

		Camera* updateProportions		(const unsigned int width, const unsigned int height);
		Camera* setNearClip				(const float value);
		Camera* setFarClip				(const float value);
		Camera* setFov					(const float value);
		Camera* refreshProjectionMatrix	();
	};
}

#endif // !CAMERA_H_

