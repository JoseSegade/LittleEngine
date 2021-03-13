#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>

namespace LittleEngine 
{
	class Texture {
	private:
		std::string name;
		unsigned int id;
		int width;
		int height;
	public:
		Texture(const char* name);
		~Texture();
				
		Texture(Texture const&) = delete;
		Texture operator=(Texture const &) = delete;

		Texture* loadFromFile(const char* path);
		Texture* Bind();
		Texture* Unbind();
	};
}

#endif // !TEXTURE_H_

