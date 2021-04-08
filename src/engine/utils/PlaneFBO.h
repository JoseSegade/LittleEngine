#pragma once
#ifndef PLANEFBO_H_
#define PLANEFBO_H_

#include <vector>
#include <glm/glm.hpp>

namespace LittleEngine
{
	namespace Utils {
		namespace PlaneFBO {
			const unsigned int verticesCount = 4;

			const std::vector<glm::vec3> vertices{
				glm::vec3(-1.f, -1.f, 0.f),
				glm::vec3(1.f, -1.f, 0.f),
				glm::vec3(-1.f,  1.f, 0.f),
				glm::vec3(1.f,  1.f, 0.f),
			};
		}
	}
}

#endif // PLANE_H_

