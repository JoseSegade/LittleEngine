#pragma once
#ifndef VERTEX_H_
#define VERTEX_H_

#include <glm/glm.hpp>

namespace LittleEngine 
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
	};
}

#endif // !VERTEX_H_
