#pragma once
#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace LittleEngine
{
	class Transform
	{
	public:
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		Transform();
		~Transform();

		Transform* CopyFrom					(Transform* transform);
		glm::mat4 GetTransformationMatrix	();
		Transform* SetParent				(Transform* transform);
		glm::vec3 ToWorldPosition			();
	private:
		Transform* parent;
	};
}

#endif // !TRANSFORM_H_