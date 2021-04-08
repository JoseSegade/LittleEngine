#include "BufferArrayObject.h"

void LittleEngine::BufferArrayObject::disableAllAttributes()
{
	for (const AttributeVariable * atttribute : attributes)
	{
		glDisableVertexAttribArray(atttribute->id);
	}
}

LittleEngine::BufferArrayObject::BufferArrayObject(GLenum dataType, GLenum bufferType,
	GLenum renderMode, bool normalized) :
	BufferObject(dataType, bufferType, renderMode), stride(0), sizePerElement(0), attributes(), normalized(normalized)
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

	for (AttributeVariable* attribute : attributes)
	{
		attribute->offset = sizePerElement;
		glVertexAttribPointer(attribute->id, attribute->count, dataType, normalized, stride, (void*)attribute->offset);
		glEnableVertexAttribArray(attribute->id);
		this->attributes.push_back(attribute);
		
		sizePerElement += attribute->count;

		stride			= sizePerElement * calculateDataSize();
	}
	return this;
}

LittleEngine::BufferArrayObject* LittleEngine::BufferArrayObject::render()
{
	glDrawElements(renderMode, size, bufferType, nullptr);
	return this;
}


