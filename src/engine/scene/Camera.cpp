#include "Camera.h"

LittleEngine::Camera::Camera(unsigned int id, const char* name, CameraProjection cameraProjection): 
	GameObject(id, name), cameraProjection(cameraProjection), projMat(1.f), farClip(100.f), nearClip(0.001f),
	width(1), height(1), fov(60.f)
{
}

LittleEngine::Camera::Camera(unsigned int id, const char* name, Transform* t, CameraProjection cameraProjection):
	GameObject(id, name, t), cameraProjection(cameraProjection), projMat(1.f), farClip(100.f), nearClip(0.001f),
	width(1), height(1), fov(60.f)
{
}

LittleEngine::Camera::~Camera()
{
	delete[] this;
}

LittleEngine::Camera* LittleEngine::Camera::updateProportions(const unsigned int width, const unsigned int height)
{
	this->width = width;
	this->height = height;
	refreshProjectionMatrix();
	return this;
}

LittleEngine::Camera* LittleEngine::Camera::setNearClip(const float value)
{
	nearClip = value;
	refreshProjectionMatrix();
	return this;
}

LittleEngine::Camera* LittleEngine::Camera::setFarClip(const float value)
{
	farClip = value;
	refreshProjectionMatrix();
	return this;
}

LittleEngine::Camera* LittleEngine::Camera::setFov(const float value)
{
	fov = value;
	refreshProjectionMatrix();
	return this;
}

LittleEngine::Camera* LittleEngine::Camera::refreshProjectionMatrix()
{
	switch (cameraProjection)
	{
	case CameraProjection::ORTOGRAPHIC:
	{
		float ar = width / height;
		projMat = glm::ortho(-(float)width / ((float)width / 2.f),
							  (float)width / ((float)width / 2.f),
			                  (float)height / ((float)height / 2.f),
			                 -(float)height / ((float)height / 2.f), 
			                 -farClip, 
			                  farClip);
		break;
	}
	case CameraProjection::PERSPECTIVE:
		projMat = glm::perspective(glm::radians(fov), (float)width / (float)height, nearClip, farClip);
		break;
	default:
		break;
	}
	return this;
}
