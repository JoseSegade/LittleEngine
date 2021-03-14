#include "Texture.h"

bool LittleEngine::Texture::isTexturePowerOf2()
{
	return isIntPowerOf2(width) && isIntPowerOf2(height);
}

bool LittleEngine::Texture::isIntPowerOf2(int number)
{
	return (number & (number - 1)) == 0;
}

LittleEngine::Texture::Texture(const char* name): id(0), name(name), width(0), height(0), state(TextureState::UNLOADED)
{
}

LittleEngine::Texture::~Texture()
{
	unbind();
	glDeleteTextures(1, &id);
}

LittleEngine::Texture* LittleEngine::Texture::loadFromFile(const char* path)
{
	unsigned char* map = Utils::loadImageFromFile(path, &width, &height);
	if (!map) return this;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, (void*)map);
	delete[] map;
	if (isTexturePowerOf2())
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	state = TextureState::LOADED;
	
	return this;
}

LittleEngine::Texture* LittleEngine::Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
	return this;
}

LittleEngine::Texture* LittleEngine::Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	return this;
}


