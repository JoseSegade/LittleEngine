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
		bool								normalized;

		void disableAllAttributes();
	public:
		BufferArrayObject(GLenum dataType = GL_FLOAT, GLenum bufferType = GL_ARRAY_BUFFER, bool normalized = false);
		~BufferArrayObject();

		BufferArrayObject* bind				() override;
		BufferArrayObject* unbind			() override;
		BufferArrayObject* generateVAO		();
		BufferArrayObject* addBufferObject	(BufferObject& vbo, std::vector<AttributeVariable*> attributes);

		inline BufferArrayObject* setSize(int value) { size = value; return this; }
	};
}

#endif // !BUFFERARRAYOBJECT_H_

