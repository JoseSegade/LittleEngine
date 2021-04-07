#include "ObjectManager.h"

LittleEngine::Mesh* LittleEngine::ObjectManager::loadMesh(const char* name, const char* path)
{
	if (meshes.count(name) > 0) 
	{
		LittleEngine::Utils::printWarning(("There is already a mesh with the name" + std::string(name)).c_str(), __FILE__, __LINE__);
		return meshes[name];
	}
	meshes[name] = new Mesh(std::string(name));
	LittleEngine::Utils::readOBJ(path, *meshes[name]);

	return meshes[name];
}

LittleEngine::Mesh* LittleEngine::ObjectManager::getMesh(const char* name)
{
	if (meshes.count(name) < 1)
	{
		LittleEngine::Utils::printWarning(("There are any mesh with the name" + std::string(name)).c_str(), __FILE__, __LINE__);
		return nullptr;
	}

	return meshes[name];
}
