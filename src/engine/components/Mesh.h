#pragma once
#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <vector>
#include "engine/graphics/Vertex.h"
#include "engine/graphics/Triangle.h"

namespace LittleEngine 
{
	class Mesh 
	{
		
	public:
		std::string				name;
		std::vector<Triangle>	triangles;
		std::vector<Vertex>		vertices;

		Mesh(std::string name) : name(name), vertices(), triangles() {}
		~Mesh() 
		{ 
			triangles.clear();
			vertices.clear();
		};

		Mesh(const Mesh&)			= delete;
		void operator=(Mesh const&) = delete;
	};
}

#endif // !MESH_H_