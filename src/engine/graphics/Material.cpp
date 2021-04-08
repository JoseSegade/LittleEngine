#include "Material.h"

LittleEngine::Material::Material(const char* name) : name(name), textures()
{

}

LittleEngine::Material::~Material()
{
	// Don't delete program object from here;
	textures.clear();
	delete[] this;
}

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

LittleEngine::Material* LittleEngine::Material::bindMaterialToProgram(ProgramObject* program)
{
	//	TODO: If material has more uniform params add them to program.
	unsigned int textureId = 0;
	for (std::pair<std::string, Texture*> texture : textures)
	{
		texture.second->bind(textureId);
		program->setUniform1i(texture.second->getUniformLocation(), textureId);

		++textureId;
	}

	return this;
}
