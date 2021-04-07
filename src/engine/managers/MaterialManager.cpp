#include "MaterialManager.h"

LittleEngine::MaterialManager* LittleEngine::MaterialManager::createMaterial(const char* name)
{
	if (materials.count(name) > 0)
	{
		Utils::printWarning("This material has already created.", __FILE__, __LINE__);
		return this;
	}
	materials[name] = new Material(name);
	return this;
}

LittleEngine::Material* LittleEngine::MaterialManager::getMaterial(const char* name)
{
	if (materials.count(name) < 1)
	{
		Utils::printWarning("Can't found the requested material.", __FILE__, __LINE__);
		return nullptr;
	}
	return materials[name];
}

/**
* This operation has no undo.
*
*/
LittleEngine::MaterialManager* LittleEngine::MaterialManager::deleteMaterial(const char* name)
{
	if (materials.count(name) < 1)
	{
		Utils::printWarning("Can't found the requested material to remove.", __FILE__, __LINE__);
		return this;
	}
	Material* mat = materials[name];
	materials.erase(name);
	delete mat;
	return this;
}

LittleEngine::MaterialManager* LittleEngine::MaterialManager::loadTexture(const char* name, const char* path)
{
	if (textures.count(name) > 0)
	{
		Utils::printWarning("This texture has already created.", __FILE__, __LINE__);
		return this;
	}
	textures[name] = new Texture(name);
	textures[name]->loadFromFile(path);
	return this;
}

LittleEngine::Texture* LittleEngine::MaterialManager::getTexture(const char* name)
{
	if (textures.count(name) < 1)
	{
		Utils::printWarning("Can't found the requested texture.", __FILE__, __LINE__);
		return nullptr;
	}
	return textures[name];
}

/**
* This operation has no undo.
*
*/
LittleEngine::MaterialManager* LittleEngine::MaterialManager::deleteTexture(const char* name)
{
	if (textures.count(name) < 1)
	{
		Utils::printWarning("Can't found the requested texture to remove.", __FILE__, __LINE__);
		return this;
	}
	
	Texture* tex = textures[name];
	textures.erase(name);
	delete tex;
	return this;
}

LittleEngine::MaterialManager* LittleEngine::MaterialManager::asignTextureToMaterial(const char* textureName, const char* materialName)
{
	if (textures.count(textureName) < 1)
	{
		Utils::printWarning("Can't found the requested texture to remove.", __FILE__, __LINE__);
		return this;
	}

	if (materials.count(materialName) < 1)
	{
		Utils::printWarning("Can't found the requested material to remove.", __FILE__, __LINE__);
		return this;
	}

	materials[materialName]->addTexture(textureName, textures[textureName]);
	return this;
}
