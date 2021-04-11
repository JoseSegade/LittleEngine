#pragma once
#define NAME_LENGHT 32
#ifndef SHADERVARIABLE_H_
#define SHADERVARIABLE_H_

#include <glad/glad.h>

namespace LittleEngine
{
	struct ShaderVariable 
	{
		GLint		id;
		GLenum		type;
		GLint		size;
		GLchar		name[NAME_LENGHT];
		GLsizei		length;
	};
}

#endif // !SHADERVARIABLE_H_

