#include "FrameBufferObject.h"

LittleEngine::FrameBufferObject::~FrameBufferObject()
{
	glDeleteBuffers(1, &planeVBOid);
	glDeleteVertexArrays(1, &planeVAOid);
	glDeleteFramebuffers(1, &id);
	glDeleteTextures(1, &colorBufferTextureId);
	glDeleteTextures(1, &depthBufferTextureId);
	glDeleteTextures(1, &positionBufferTextureId);
	delete[] this;
}

LittleEngine::FrameBufferObject* LittleEngine::FrameBufferObject::setColorTextureLocation(const int value)
{
	colorTextureLocation = value;
	return this;
}

LittleEngine::FrameBufferObject* LittleEngine::FrameBufferObject::setPositionTextureLocation(const int value)
{
	positionTextureLocation = value;
	return this;
}

LittleEngine::FrameBufferObject* LittleEngine::FrameBufferObject::setFrameVAO()
{
	glGenVertexArrays(1, &planeVAOid);
	glBindVertexArray(planeVAOid);

	glGenBuffers(1, &planeVBOid);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBOid);

	std::vector<float> planeVertexPostions;
	planeVertexPostions.reserve(Utils::PlaneFBO::verticesCount * 3);
	for (const glm::vec3 vertex : Utils::PlaneFBO::vertices)
	{
		planeVertexPostions.push_back(vertex.x);
		planeVertexPostions.push_back(vertex.y);
		planeVertexPostions.push_back(vertex.z);
	}

	glBufferData(GL_ARRAY_BUFFER, planeVertexPostions.size() * sizeof(float),
		&planeVertexPostions[0], GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Not sure if memory persistant.
	planeVertexPostions.clear();

	return this;
}

LittleEngine::FrameBufferObject* LittleEngine::FrameBufferObject::generate()
{
	glGenFramebuffers(1, &id);
	glGenTextures(1, &colorBufferTextureId);
	glGenTextures(1, &depthBufferTextureId);
	glGenTextures(1, &positionBufferTextureId);
	return this;
}

LittleEngine::FrameBufferObject* LittleEngine::FrameBufferObject::resize(unsigned int width, unsigned int height)
{
	glBindTexture(GL_TEXTURE_2D, colorBufferTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);


	glBindTexture(GL_TEXTURE_2D, positionBufferTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);


	glBindTexture(GL_TEXTURE_2D, depthBufferTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, colorBufferTextureId   , 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, positionBufferTextureId, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT , GL_TEXTURE_2D, depthBufferTextureId   , 0);

	const GLenum buffs[] = { GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(2, buffs);

	if (GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER))
	{
		printf("Something gone wrong configuring FBO");
		exit(-1);
	}
	return this;
}

LittleEngine::FrameBufferObject* LittleEngine::FrameBufferObject::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	return this;
}

LittleEngine::FrameBufferObject* LittleEngine::FrameBufferObject::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return this;
}

void LittleEngine::FrameBufferObject::render(ProgramObject* program)
{
	glBindVertexArray(planeVAOid);

	if (colorTextureLocation != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorBufferTextureId);
		program->setUniform1i(colorTextureLocation, 0);
	}

	if (positionTextureLocation != -1)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, positionBufferTextureId);
		program->setUniform1i(positionTextureLocation, 1);
	}

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
