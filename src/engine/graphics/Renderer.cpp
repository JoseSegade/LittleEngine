#include "Renderer.h"

LittleEngine::Renderer::Renderer(): bgColor(glm::vec4(0.f, 0.f, 0.f, 1.f))
{
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
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::clearBuffersPP()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return this;
}

LittleEngine::Renderer* LittleEngine::Renderer::resize(int width, int height)
{
    glViewport(0, 0, width, height);
    resizeFbo(width, height);
    return this;
}
