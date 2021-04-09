#pragma once
#ifndef BUFFERARRAYOBJECT_H_
#define BUFFERARRAYOBJECT_H_

#include <vector>
#include <glad/glad.h>
#include "BufferObject.h"
#include "AttributeVariable.h"

namespace LittleEngine 
{
	class BufferArrayObject : public BufferObject
	{
	private:
		std::vector<AttributeVariable*>		attributes;
		GLenum								renderMode;
		unsigned int						sizePerElement;
		bool								normalized;

		void disableAllAttributes();
	public:
		BufferArrayObject(GLenum dataType = GL_FLOAT, GLenum bufferType = GL_ARRAY_BUFFER, GLenum renderMode = GL_TRIANGLES, bool normalized = false);
		~BufferArrayObject();

		BufferArrayObject* bind				() override;
		BufferArrayObject* unbind			() override;
		BufferArrayObject* render			() override;
		BufferArrayObject* generateVAO		();
		BufferArrayObject* addBufferObject	(BufferObject& vbo, std::vector<AttributeVariable*> attributes);
	};
}

#endif // !BUFFERARRAYOBJECT_H_

