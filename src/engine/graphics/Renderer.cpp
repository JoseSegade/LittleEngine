#include "Renderer.h"

LittleEngine::Renderer::Renderer(): bgColor(glm::vec4(0.f, 0.f, 0.f, 1.f)), fbo(nullptr)
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

LittleEngine::Renderer* LittleEngine::Renderer::createFBO()
{
    fbo = new FrameBufferObject();
    fbo ->generate   ()
        ->setFrameVAO();
    return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::changeBackgroungColor(glm::vec4 color)
{
    bgColor = color;
    return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::startRenderConfig()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::resize(int width, int height)
{
    glViewport(0, 0, width, height);
    fbo->resize(width, height);
    return this;
}
