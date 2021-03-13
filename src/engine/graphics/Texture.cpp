#include "Texture.h"

LittleEngine::Texture::Texture(const char* name): name(name), width(0.), height(0.)
{
}

LittleEngine::Texture::~Texture()
{
	Unbind();
}

LittleEngine::Texture* LittleEngine::Texture::loadFromFile(const char* path)
{
	return this;
}


