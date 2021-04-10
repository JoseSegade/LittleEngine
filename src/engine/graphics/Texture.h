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
		int				shaderUniformVariableId;
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

		inline int			getUniformLocation	()							const	{ return shaderUniformVariableId; }
		inline void			setUniformLocation	(int value)							{ shaderUniformVariableId = value; }
		Texture*			loadFromFile		(const char* path);
		Texture*			bind				(unsigned int idTexture);
		Texture*			unbind				();
	};
}

#endif // !TEXTURE_H_

