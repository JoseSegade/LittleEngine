#pragma once
#ifndef BUFFERARRAYOBJECT_H_
#define BUFFERARRAYOBJECT_H_

#include <vector>
#include <glad/glad.h>
#include "BufferObject.h"
#include "AttributeVariable.h"

namespace LittleEngine 
{
	class BufferArrayObject : BufferObject
	{
	private:
		std::vector<AttributeVariable*>		attributes;
		GLenum								renderMode;
		unsigned int						sizePerElement;
		unsigned int						stride;
	public:
		BufferArrayObject(GLenum dataType = GL_FLOAT, GLenum bufferType = GL_ARRAY_BUFFER, GLenum renderMode = GL_TRIANGLES);
		~BufferArrayObject();


	};
}

#endif // !BUFFERARRAYOBJECT_H_

