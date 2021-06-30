#pragma once
#ifndef BUFFEROBJECT_H_
#define BUFFEROBJECT_H_

#include <glad/glad.h>
#include "engine/graphics/ProgramObject.h"

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

		inline GLenum			getDataType		() const { return dataType; }
		inline void             setBufferType   (GLenum value) { bufferType = value; }

		virtual BufferObject*   bind              ();
		virtual BufferObject*	bindAsVertexArray ();
		virtual BufferObject*	unbind			  ();
		virtual BufferObject*	render			  (LittleEngine::RenderMode renderMode = LittleEngine::RenderMode::TRIANGLES);

		virtual BufferObject*	addDataToShader	               (const void* data, int size);
		virtual BufferObject*   addDataToShaderSpecifyDataSize (const void* data, int size, int dataSize);
		virtual BufferObject*   bindBufferBase                 (int bufferLocation);
		virtual BufferObject*   compute                        (int blocksCount);

		virtual void* mapBufferOnObject(int size);
		virtual BufferObject* unmapBuffer();
	};
}

#endif // !BUFFEROBJECT_H_

