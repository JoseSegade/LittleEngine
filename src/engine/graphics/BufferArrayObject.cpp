#include "BufferArrayObject.h"

LittleEngine::BufferArrayObject::BufferArrayObject(GLenum dataType, GLenum bufferType, GLenum renderMode) : 
	BufferObject(dataType, bufferType), stride(0), sizePerElement(0), renderMode(renderMode), attributes()
{	
}

LittleEngine::BufferArrayObject::~BufferArrayObject()
{
	for (const AttributeVariable* attributeVariable : attributes)
	{
		glDisableVertexAttribArray(attributeVariable->id);
	}
	delete[] this;
}


