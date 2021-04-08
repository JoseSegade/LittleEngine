#include "MeshRenderer.h"

LittleEngine::MeshRenderer::~MeshRenderer()
{
	delete vao;
	delete indexBuffer;
	delete[] this;
}

void LittleEngine::MeshRenderer::initializeVAOData(ProgramObject* program)
{
	// TODO: Optimice this monstuous chunk of code.

	if (mesh == nullptr)
	{
		Utils::printWarning("Error at initializing VAO data, Mesh is not asigned to this MeshRenderer.", __FILE__, __LINE__);
		return;
	}

	vao					= new BufferArrayObject	(GL_FLOAT, GL_ARRAY_BUFFER, GL_TRIANGLES, GL_FALSE);
	vao->generateVAO();

	BufferObject* vbo	= new BufferObject		(GL_FLOAT, GL_ARRAY_BUFFER);

	std::vector<float>				vertexValues;
	std::vector<AttributeVariable*>	attributeValues;


	// Number of vertices times vertices properties: 3xyz-pos + 3xyz-normals + 2uv-texcoords + 3rgb-color = 11
	vertexValues.reserve(mesh->vertices.size() * 11);

	for (size_t i = 0; i < mesh->vertices.size(); ++i)
	{
		vertexValues.push_back(mesh->vertices[i].position.x);
		vertexValues.push_back(mesh->vertices[i].position.y);
		vertexValues.push_back(mesh->vertices[i].position.z);

		vertexValues.push_back(mesh->vertices[i].texCoord.x);
		vertexValues.push_back(mesh->vertices[i].texCoord.y);

		vertexValues.push_back(mesh->vertices[i].normal.x);
		vertexValues.push_back(mesh->vertices[i].normal.y);
		vertexValues.push_back(mesh->vertices[i].normal.z);

		vertexValues.push_back(mesh->vertices[i].color.r);
		vertexValues.push_back(mesh->vertices[i].color.g);
		vertexValues.push_back(mesh->vertices[i].color.b);
	}

	vbo->addDataToShader(&vertexValues[0], vertexValues.size());

	attributeValues.reserve(4);

	attributeValues.push_back(new AttributeVariable(program->getVariableId("inPos"     , LittleEngine::VariableType::ATTRIBUTE), 3));
	attributeValues.push_back(new AttributeVariable(program->getVariableId("inTexCoord", LittleEngine::VariableType::ATTRIBUTE), 2));
	attributeValues.push_back(new AttributeVariable(program->getVariableId("inNormal"  , LittleEngine::VariableType::ATTRIBUTE), 3));
	attributeValues.push_back(new AttributeVariable(program->getVariableId("inColor"   , LittleEngine::VariableType::ATTRIBUTE), 3));

	vao->addBufferObject(*vbo, attributeValues);

	indexBuffer = new BufferObject(GL_UNSIGNED_INT, GL_ELEMENT_ARRAY_BUFFER);

	std::vector<unsigned int> triangleValues;

	// Number of triangle indices: 3;
	triangleValues.reserve(mesh->triangles.size() * 3);
	for (size_t i = 0; i < mesh->triangles.size(); ++i)
	{
		triangleValues.push_back(mesh->triangles[i].a);
		triangleValues.push_back(mesh->triangles[i].b);
		triangleValues.push_back(mesh->triangles[i].c);
	}

	indexBuffer->addDataToShader(&triangleValues[0], triangleValues.size());

	vertexValues.clear();
	attributeValues.clear();
	triangleValues.clear();
}

void LittleEngine::MeshRenderer::onStart()
{
}

void LittleEngine::MeshRenderer::onUpdate(double deltaTime)
{
}

void LittleEngine::MeshRenderer::onRender(ProgramObject* program, ViewProj &viewProj)
{
	unsigned int modelLocation = program->getVariableId("model", LittleEngine::VariableType::UNIFORM);
	program->setUniformMatrix4fv(modelLocation, &gameObject->transform->GetTransformationMatrix()[0][0], 1);
	vao->bind();
	indexBuffer->render();
}