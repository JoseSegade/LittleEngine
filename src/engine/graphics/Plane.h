#pragma once
#ifndef PLANE_H_
#define PLANE_H_

#include <vector>
#include <glm/glm.hpp>

namespace LittleEngine
{
	struct Plane
	{
		const unsigned int verticesCount = 4;

		const std::vector<glm::vec3> vertices{
			glm::vec3(-1.f, -1.f, 0.f),
			glm::vec3( 1.f, -1.f, 0.f),
			glm::vec3(-1.f,  1.f, 0.f),
			glm::vec3( 1.f,  1.f, 0.f),
		};

	};
}

#endif // PLANE_H_

