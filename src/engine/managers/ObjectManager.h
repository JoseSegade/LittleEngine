#pragma once
#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include <string>
#include <unordered_map>
#include "engine/managers/ISingleton.h"
#include "engine/components/Mesh.h"
#include "engine/utils/Logger.h"
#include "engine/utils/OBJReader.h"

namespace LittleEngine
{
	class ObjectManager : public ISingleton<ObjectManager>
	{
	private:
		std::unordered_map<std::string, Mesh*> meshes;
	public:
		// TODO: CRUD of meshes
		Mesh* loadMesh	(const char* name, const char* path);
		Mesh* getMesh	(const char* name);

		void  destroy	() override;
	};
}

#endif // !OBJECTMANAGER_H_

