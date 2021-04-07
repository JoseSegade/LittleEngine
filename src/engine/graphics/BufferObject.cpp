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

LittleEngine::BufferObject::BufferObject(GLenum dataType, GLenum bufferType):
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

LittleEngine::BufferObject* LittleEngine::BufferObject::unbind()
{
	glBindBuffer(bufferType, 0);
	return this;
}

LittleEngine::BufferObject* LittleEngine::BufferObject::addDataToShader(const void* data, int size)
{
	this->size = size;
	glGenBuffers(1, &id);
	glBindBuffer(bufferType, id);
	unsigned int sizeTimesData = size * calculateDataSize();
	glBufferData(bufferType, sizeTimesData, data, GL_STATIC_DRAW);
	return this;
}
