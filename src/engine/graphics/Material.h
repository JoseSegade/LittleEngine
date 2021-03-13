#pragma once
#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ProgramObject.h"

namespace LittleEngine
{
	class Material
	{
	private:
		std::string name;
		glm::vec3 Ka;
		glm::vec3 Kd;
		glm::vec3 Ks;

		Texture* colorTex;
		Texture* emissiveTex;
		Texture* specularTex;
		Texture* normalMap;
		Texture* bumpMap;

		ProgramObject* programObject;
	};
}

#endif // !MATERIAL_H_

