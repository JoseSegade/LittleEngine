#include "Material.h"

LittleEngine::Material::Material(const char* name) : name(name), textures()
{

}

LittleEngine::Material::~Material()
{
	// Don't delete program object from here;
	textures.clear();
	properties.clear();
	delete[] this;
}

#pragma region TEXTURES

LittleEngine::Material* LittleEngine::Material::addTexture(const char* name, Texture* texture)
{
	if (textures.count(name) > 0)
	{
		Utils::printWarning("Can't add a previously added texture.", __FILE__, __LINE__);
		return this;
	}
	textures[name] = texture;

	return this;
}

LittleEngine::Texture* LittleEngine::Material::changeTexture(const char* name, Texture* texture)
{
	if (textures.count(name) < 1)
	{
		Utils::printWarning("Can't find the requested texture.", __FILE__, __LINE__);
		return nullptr;
	}

	//	Returns previously added texture.
	Texture* ret = textures[name];
	textures[name] = texture;
	return ret;
}

LittleEngine::Texture* LittleEngine::Material::getTexture(const char* name)
{
	if (textures.count(name) < 1)
	{
		Utils::printWarning("Can't find the requested texture.", __FILE__, __LINE__);
		return nullptr;
	}

	return textures[name];
}

LittleEngine::Texture* LittleEngine::Material::removeTexture(const char* name)
{
	if (textures.count(name) < 1)
	{
		Utils::printWarning("Can't find the requested texture.", __FILE__, __LINE__);
		return nullptr;
	}

	//	Returns previously added texture.
	Texture* ret = textures[name];
	textures.erase(name);
	return ret;
}

#pragma endregion

#pragma region PROPERTIES

LittleEngine::Material* LittleEngine::Material::addProperty(const char* name, glm::vec3 value)
{
	if (properties.count(name) > 0)
	{
		Utils::printWarning("Can't add a previously added property.", __FILE__, __LINE__);
		return this;
	}
	properties[name] = value;

	return this;
}

glm::vec3 LittleEngine::Material::changeProperty(const char* name, glm::vec3 value)
{
	if (properties.count(name) < 1)
	{
		Utils::printWarning("Can't find the requested property.", __FILE__, __LINE__);
		return glm::vec3(0.f);
	}
	glm::vec3 ret = properties[name];
	properties[name] = value;
	return ret;
}

glm::vec3 LittleEngine::Material::getProperty(const char* name)
{
	if (properties.count(name) < 1)
	{
		Utils::printWarning("Can't find the requested property.", __FILE__, __LINE__);
		return glm::vec3(0.f);
	}

	return properties[name];
}

glm::vec3 LittleEngine::Material::removeProperty(const char* name)
{
	if (properties.count(name) < 1)
	{
		Utils::printWarning("Can't find the requested property.", __FILE__, __LINE__);
		return glm::vec3(0.f);
	}
	glm::vec3 ret = properties[name];
	properties.erase(name);
	return ret;
}

#pragma endregion

LittleEngine::Material* LittleEngine::Material::bindMaterialToProgram(ProgramObject* program)
{
	//	TODO: If material has more uniform params add them to program.
	unsigned int textureId = 0;
	for (std::pair<std::string, Texture*> texture : textures)
	{
		if (texture.second->getUniformLocation() > -1)
		{
			texture.second->bind(textureId);
			program->setUniform1i(texture.second->getUniformLocation(), textureId);

			++textureId;
		}
	}

	for (std::pair<std::string, glm::vec3> prop : properties)
	{
		int propLocation = program->getVariableId(prop.first, VariableType::UNIFORM);
		if (propLocation > -1)
		{
			const float vector[] = { prop.second.x, prop.second.y, prop.second.z };
			program->setUniform3fv(propLocation, &vector[0]);
		}
	}


	return this;
}
