#include "BufferArrayObject.h"

void LittleEngine::BufferArrayObject::disableAllAttributes()
{
	for (const AttributeVariable * atttribute : attributes)
	{
		glDisableVertexAttribArray(atttribute->id);
	}
}

LittleEngine::BufferArrayObject::BufferArrayObject(GLenum dataType, GLenum bufferType, bool normalized) :
	BufferObject(dataType, bufferType), attributes(), normalized(normalized)
{	
}

LittleEngine::BufferArrayObject::~BufferArrayObject()
{
	disableAllAttributes();
	glDeleteVertexArrays(1, &id);
	delete[] this;
}

LittleEngine::BufferArrayObject* LittleEngine::BufferArrayObject::bind()
{
	glBindVertexArray(id);
	return this;
}

LittleEngine::BufferArrayObject* LittleEngine::BufferArrayObject::unbind()
{
	disableAllAttributes();
	BufferObject::unbind();
	return this;
}

LittleEngine::BufferArrayObject* LittleEngine::BufferArrayObject::generateVAO()
{
	glGenVertexArrays(1, &id);
	return this;
}

LittleEngine::BufferArrayObject* LittleEngine::BufferArrayObject::addBufferObject(BufferObject &vbo, std::vector<AttributeVariable*> attributes)
{
	bind();
	vbo.bind();

	int sizePerElement = 0;
	for (AttributeVariable* attribute : attributes)
	{
		attribute->offset = sizePerElement;
		unsigned int offsetTimesDataSize = attribute->offset * calculateDataSize();
		if (attribute->id > -1) glEnableVertexAttribArray(attribute->id);
		if (attribute->id > -1) glVertexAttribPointer(attribute->id, attribute->count, dataType, normalized, attribute->stride, (void*)offsetTimesDataSize);
		this->attributes.push_back(attribute);

		sizePerElement += attribute->count;
	}
	return this;
}


