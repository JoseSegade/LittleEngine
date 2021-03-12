#include "Transform.h"

namespace LittleEngine {
	Transform::Transform() : 
		position(glm::vec3(0.f)), rotation(glm::quat(1.f,0.f,0.f,0.f)), scale (glm::vec3(1.f)), parent(nullptr)
	{
	}

	Transform::~Transform()
	{
	}

	glm::mat4 Transform::GetTransformationMatrix()
	{
		glm::mat4 ret = glm::mat4(1.f);
		ret = glm::translate(ret, this->position);
		glm::mat4 rot = glm::toMat4(this->rotation);
		ret = ret * rot;
		ret = glm::scale(ret, this->scale);

		return ret;
	}

	Transform* Transform::CopyFrom(Transform* transform)
	{
		this->position = transform->position;
		this->rotation = transform->rotation;
		this->scale = transform->scale;
		return this;
	}

	Transform* Transform::SetParent(Transform* transform) 
	{
		this->parent = transform;
		return this;
	}

	glm::vec3 Transform::ToWorldPosition() 
	{
		if (!this->parent) 
		{
			return this->position;
		}

		glm::mat4 worldMatrix = this->GetTransformationMatrix() * this->parent->GetTransformationMatrix();
		return glm::vec3(worldMatrix[4].x, worldMatrix[4].y, worldMatrix[4].z);
	}
}