#pragma once
#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ProgramObject.h"
#include "engine/graphics/Texture.h"
#include "engine/utils/Logger.h"

namespace LittleEngine
{
	class Material
	{
	private:
		std::string name;

		std::unordered_map<std::string, Texture*> textures;

	public: 
		Material(const char* name);
		~Material();

		Material(const Material&)		= delete;
		void operator=(Material const&) = delete;

		Material*	addTexture				(const char* name, Texture* texture);
		Texture*	changeTexture			(const char* name, Texture* texture);
		Texture*	getTexture				(const char* name);
		Texture*	removeTexture			(const char* name);
		Material*	bindMaterialToProgram	(ProgramObject* program);
	};
}

#endif // !MATERIAL_H_

