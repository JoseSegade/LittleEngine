#pragma once
#ifndef OBJREADER_H_
#define OBJREADER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/graphics/Vertex.h"
#include "engine/graphics/Triangle.h"
#include "engine/components/Mesh.h"

namespace LittleEngine
{
	namespace Utils
	{
		void readOBJ(const char* path, Mesh &mesh);
	}
}

#endif // !OBJREADER_H_

