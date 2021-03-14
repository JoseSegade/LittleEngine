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

LittleEngine::BufferObject::BufferObject(GLenum dataType = GL_FLOAT, GLenum bufferType = GL_ARRAY_BUFFER):
	dataType(dataType), bufferType(bufferType), id(0), count(0)
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

LittleEngine::BufferObject* LittleEngine::BufferObject::addDataToShader(const void* data, unsigned int count)
{
	this->count = count;
	glBindBuffer(bufferType, id);
	glBufferData(bufferType, count * calculateDataSize(), data, GL_STATIC_DRAW);
	return this;
}
