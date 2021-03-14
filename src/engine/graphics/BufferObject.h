#pragma once
#ifndef BUFFEROBJECT_H_
#define BUFFEROBJECT_H_

#include <glad/glad.h>

namespace LittleEngine 
{
	class BufferObject
	{
	private:
		unsigned int	id;
		GLenum			bufferType;
		GLenum			dataType;
		unsigned int	count;

	protected:
		unsigned int calculateDataSize();

	public:
		BufferObject(GLenum dataType = GL_FLOAT, GLenum bufferType = GL_ARRAY_BUFFER);
		~BufferObject();

		virtual BufferObject* bind				();
		virtual BufferObject* unbind			();

		virtual BufferObject* addDataToShader	(const void* data, unsigned int count);
	};
}

#endif // !BUFFEROBJECT_H_

