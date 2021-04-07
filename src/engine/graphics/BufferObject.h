#pragma once
#ifndef BUFFEROBJECT_H_
#define BUFFEROBJECT_H_

#include <glad/glad.h>

namespace LittleEngine 
{
	class BufferObject
	{
	protected:
		unsigned int	id;
		GLenum			bufferType;
		GLenum			dataType;
		unsigned int	size;

		unsigned int calculateDataSize();

	public:
		BufferObject(GLenum dataType = GL_FLOAT, GLenum bufferType = GL_ARRAY_BUFFER);
		~BufferObject();

		inline GLenum getDataType() const { return dataType; }

		virtual BufferObject* bind				();
		virtual BufferObject* unbind			();

		virtual BufferObject* addDataToShader	(const void* data, int size);
	};
}

#endif // !BUFFEROBJECT_H_

