#include "BufferObject.h"

unsigned int LittleEngine::BufferObject::calculateDataSize()
{
	switch (dataType)
	{
	case GL_FLOAT:
	case GL_INT:
	case GL_UNSIGNED_INT:
		return 4;
	case GL_SHORT:
	case GL_UNSIGNED_SHORT:
		return 2;
	case GL_BYTE:
	case GL_UNSIGNED_BYTE:
		return 1;
	default:
		break;
	}
	return 0;
}

LittleEngine::BufferObject::BufferObject(GLenum dataType, GLenum bufferType) :
	dataType(dataType), bufferType(bufferType), id(0), size(0)
{
}

LittleEngine::BufferObject::~BufferObject()
{
	glDeleteBuffers(1, &id);
}

LittleEngine::BufferObject* LittleEngine::BufferObject::bind()
{
	glBindBuffer(bufferType, id);
	return this;
}

LittleEngine::BufferObject* LittleEngine::BufferObject::bindAsVertexArray()
{
	glBindVertexArray(id);
	return this;
}



LittleEngine::BufferObject* LittleEngine::BufferObject::unbind()
{
	glBindBuffer(bufferType, 0);
	return this;
}

LittleEngine::BufferObject* LittleEngine::BufferObject::render(RenderMode renderMode)
{

	switch (renderMode)
	{
	case RenderMode::TRIANGLES:
	{
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, (void*)0);
		break;
	}
	case RenderMode::QUADS:
	{
		glPatchParameteri(GL_PATCH_VERTICES, 4);
		glDrawElements(GL_PATCHES, size, GL_UNSIGNED_INT, (void*)0);
		break;
	}
	case RenderMode::TRIANGLES_PATCH:
	{
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		glDrawElements(GL_PATCHES, size, GL_UNSIGNED_INT, (void*)0);
		break;
	}
	case RenderMode::POINTS:
	{
		glDrawArrays(GL_POINTS, 0, size);
		break;
	}
	default:
		// This should never happen
		break;
	}
	
	return this;
}

LittleEngine::BufferObject* LittleEngine::BufferObject::addDataToShader(const void* data, int size)
{	
	return addDataToShaderSpecifyDataSize(data, size, calculateDataSize());
}

LittleEngine::BufferObject* LittleEngine::BufferObject::addDataToShaderSpecifyDataSize(const void* data, int size, int dataSize)
{
	this->size = size;
	glGenBuffers(1, &id);
	glBindBuffer(bufferType, id);
	unsigned int sizeTimesData = size * dataSize;
	glBufferData(bufferType, sizeTimesData, data, GL_DYNAMIC_DRAW);
	return this;
}

LittleEngine::BufferObject* LittleEngine::BufferObject::bindBufferBase(int bufferLocation)
{
	glBindBufferBase(bufferType, bufferLocation, id);
	return this;
}

LittleEngine::BufferObject* LittleEngine::BufferObject::compute(int blocksCount)
{
	glDispatchCompute(blocksCount, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	return this;
}

void* LittleEngine::BufferObject::mapBufferOnObject(int size)
{
	return glMapBufferRange(bufferType, 0, size, GL_MAP_WRITE_BIT);
}

LittleEngine::BufferObject* LittleEngine::BufferObject::unmapBuffer()
{
	glUnmapBuffer(bufferType);
	return this;
}
