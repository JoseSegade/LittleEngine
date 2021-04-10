#pragma once
#ifndef MATERIALMANAGER_H_
#define MATERIALMANAGER_H_

#include <unordered_map>
#include <string>
#include "ISingleton.h"
#include "engine/graphics/Material.h"
#include "engine/graphics/Texture.h"
#include "engine/utils/Logger.h"

namespace LittleEngine 
{
	class MaterialManager : public ISingleton<MaterialManager>
	{
	private:
		std::unordered_map<std::string, Material*> materials;
		std::unordered_map<std::string, Texture*> textures;
	public:
		// Material relative
		MaterialManager*	createMaterial			(const char* name);
		Material*			getMaterial				(const char* name);
		MaterialManager*	deleteMaterial			(const char* name);

		// Texture relative
		MaterialManager*	loadTexture				(const char* name, const char* path, const unsigned int textureId);
		Texture*			getTexture				(const char* name);
		MaterialManager*	deleteTexture			(const char* name);

		MaterialManager*	asignTextureToMaterial	(const char* textureName, const char* materialName);

		void				destroy					() override;

	};
}

#endif // !MATERIALMANAGER_H_

