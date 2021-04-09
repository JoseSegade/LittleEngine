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

	int inPos			= program->getVariableId("inPos", LittleEngine::VariableType::ATTRIBUTE);
	int inColor			= program->getVariableId("inColor", LittleEngine::VariableType::ATTRIBUTE);
	int inTexCoord		= program->getVariableId("inTexCoord", LittleEngine::VariableType::ATTRIBUTE);
	int inNormal		= program->getVariableId("inNormal", LittleEngine::VariableType::ATTRIBUTE);
	unsigned int sumVariableType = 0;

	if (inPos > -1) sumVariableType += 3;
	if (inColor > -1) sumVariableType += 3;
	if (inTexCoord > -1) sumVariableType += 2;
	if (inNormal > -1) sumVariableType += 3;

	for (size_t i = 0; i < mesh->vertices.size(); ++i)
	{
		if (inPos > -1)
		{
			vertexValues.push_back(mesh->vertices[i].position.x);
			vertexValues.push_back(mesh->vertices[i].position.y);
			vertexValues.push_back(mesh->vertices[i].position.z);
		}

		if (inColor > -1)
		{
			vertexValues.push_back(mesh->vertices[i].color.r);
			vertexValues.push_back(mesh->vertices[i].color.g);
			vertexValues.push_back(mesh->vertices[i].color.b);
		}

		if (inTexCoord > -1)
		{
			vertexValues.push_back(mesh->vertices[i].texCoord.x);
			vertexValues.push_back(mesh->vertices[i].texCoord.y);
		}

		if (inNormal > -1)
		{
			vertexValues.push_back(mesh->vertices[i].normal.x);
			vertexValues.push_back(mesh->vertices[i].normal.y);
			vertexValues.push_back(mesh->vertices[i].normal.z);
		}
	}

	vbo->addDataToShader(&vertexValues[0], vertexValues.size());

	if (inPos > -1)			attributeValues.push_back(new AttributeVariable(inPos	  , 3, sumVariableType * sizeof(float)));
	if (inColor > -1)		attributeValues.push_back(new AttributeVariable(inColor	  , 3, sumVariableType * sizeof(float)));
	if (inTexCoord > -1)	attributeValues.push_back(new AttributeVariable(inTexCoord, 2, sumVariableType * sizeof(float)));
	if (inNormal > -1)		attributeValues.push_back(new AttributeVariable(inNormal  , 3, sumVariableType * sizeof(float)));

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
	unsigned int normalLocation			= program->getVariableId("normal", LittleEngine::VariableType::UNIFORM);
	unsigned int modelViewLocation		= program->getVariableId("modelView", LittleEngine::VariableType::UNIFORM);
	unsigned int modelViewProjLocation	= program->getVariableId("modelViewProj", LittleEngine::VariableType::UNIFORM);

	glm::mat4 model			= gameObject->transform->GetTransformationMatrix();
	glm::mat4 modelView		= viewProj.view * model;
	glm::mat4 normal		= glm::transpose(glm::inverse(modelView));
	glm::mat4 modelViewProj = viewProj.proj * modelView;	

	program->setUniformMatrix4fv(normalLocation,		&normal[0][0]);
	program->setUniformMatrix4fv(modelViewLocation,		&modelView[0][0]);
	program->setUniformMatrix4fv(modelViewProjLocation, &modelViewProj[0][0]);

	vao->bind();
	indexBuffer->render();
}