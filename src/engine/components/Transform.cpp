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
		ret = glm::translate(ret, position);
		glm::mat4 rot = glm::toMat4(rotation);
		ret = ret * rot;
		ret = glm::scale(ret, scale);

		return ret;
	}

	Transform* Transform::CopyFrom(Transform* transform)
	{
		position = transform->position;
		rotation = transform->rotation;
		scale    = transform->scale;
		return this;
	}

	Transform* Transform::SetParent(Transform* transform) 
	{
		parent = transform;
		return this;
	}

	glm::vec3 Transform::ToWorldPosition() 
	{
		if (!parent) 
		{
			return position;
		}

		glm::mat4 worldMatrix = GetTransformationMatrix() * parent->GetTransformationMatrix();
		return glm::vec3(worldMatrix[4].x, worldMatrix[4].y, worldMatrix[4].z);
	}
}