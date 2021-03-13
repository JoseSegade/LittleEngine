#pragma once
#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <vector>
#include "engine/graphics/Vertex.h"

namespace LittleEngine 
{
	class Mesh 
	{
	private:
		std::string				name;
		std::vector<Vertex>		vertices;
		std::vector<int>		indices;
		
	public:
	};
}

#endif // !MESH_H_