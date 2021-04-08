#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <glad/glad.h>
#include "engine/utils/ImageLoader.h"

namespace LittleEngine 
{
	enum class TextureState
	{
		UNLOADED,
		LOADED
	};

	class Texture {
	private:
		TextureState	state;
		std::string		name;
		unsigned int	shaderUniformVariableId;
		unsigned int	id;
		int				width;
		int				height;

		bool isTexturePowerOf2();
		bool isIntPowerOf2(int number);
	public:
		Texture(const char* name);
		~Texture();
				
		Texture(Texture const&) = delete;
		Texture operator=(Texture const &) = delete;

		inline unsigned int getUniformLocation	() const { return shaderUniformVariableId; }
		Texture*			loadFromFile		(const char* path);
		Texture*			bind				(unsigned int idTexture);
		Texture*			unbind				();
	};
}

#endif // !TEXTURE_H_

