#include "Renderer.h"

LittleEngine::Renderer::Renderer(): bgColor(glm::vec4(0.6f, 0.6f, 0.6f, 1.f)), fbo(nullptr)
{
}

LittleEngine::Renderer::~Renderer()
{
    delete fbo;
    delete[] this;
}

void LittleEngine::Renderer::renderFBO(ProgramObject* programObject)
{
    fbo->render(programObject);
}

LittleEngine::Renderer* LittleEngine::Renderer::createFBO(ProgramObject* programObject)
{
    fbo = new FrameBufferObject();
    fbo->generate()
        ->setFrameVAO()
        ->setColorTextureLocation(programObject->getVariableId("colorTex", VariableType::UNIFORM))
        ->setPositionTextureLocation(programObject->getVariableId("posTex", VariableType::UNIFORM));
    return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::changeBackgroungColor(glm::vec4 color)
{
    bgColor = color;
    return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::startRenderConfig()
{
    glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
	return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::clearBuffersFw()
{
    fbo->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::clearBuffersPP()
{
    fbo->unbind();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA);
    //glBlendColor(0.3, 0.3, 0.3, 0.7);
    //glBlendEquation(GL_FUNC_ADD);
    return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::resize(int width, int height)
{
    glViewport(0, 0, width, height);
    fbo->resize(width, height);
    return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::uploadTimeToProgram(ProgramObject* program, double deltaTime)
{
    int timeLocation = program->getVariableId("inTime", VariableType::UNIFORM);
    if (timeLocation > -1)
    {
        program->setUniform1d(timeLocation, deltaTime);
    }
    return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::uploadResolutionToProgram(ProgramObject* program, unsigned int width, unsigned int height)
{
    int resolutionLocation = program->getVariableId("inResolution", VariableType::UNIFORM);
    if (resolutionLocation > -1)
    {
        const float vector[] = { width, height, 1.f };
        program->setUniform3fv(resolutionLocation, &vector[0]);
;    }
    return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::setWireframeWidth(float width, WireframeType type)
{
    if (type == WireframeType::LINE)
    {
        glLineWidth(width);
    }
    else if (type == WireframeType::POINT)
    {
        glPointSize(width);
    }
    return this;
}


