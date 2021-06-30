#include "Engine.h"

LittleEngine::Engine::Engine(const char* name, int width, int height): name(name), width(width), height(height), currentState(LittleEngine::EngineState::LOADING), lag(0.), window(), scene()
{
    if (!glfwInit())
        std::exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        std::exit(EXIT_FAILURE);

    }
   
    glfwMakeContextCurrent(window);
}

LittleEngine::Engine::~Engine()
{

}

void LittleEngine::Engine::run() 
{
    if (glfwWindowShouldClose(window)) {
        currentState = LittleEngine::EngineState::EXIT;
    }
    switch (currentState)
    {
    case LittleEngine::EngineState::PAUSE:
    case LittleEngine::EngineState::PLAY:
        mainLoop();
        break;
    case LittleEngine::EngineState::EXIT:
        exit();
        break;
    default:
        break;
    }
}

void LittleEngine::Engine::pause()
{
    currentState = LittleEngine::EngineState::PAUSE;
}

void LittleEngine::Engine::play()
{
    currentState = LittleEngine::EngineState::PLAY;
    prevTime = std::chrono::high_resolution_clock::now();
    lag = 0.;
}

void LittleEngine::Engine::init() { 
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {        
        Engine* self = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        self->resizeWindow( window,  width,  height);    
    });
    glfwSetKeyCallback(window, [](GLFWwindow* window, int k, int s, int action, int mods) {
        Engine* self = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        self->key( window, k, s, action, mods);
    });
    //glfwSetCursorPosCallback(window, cursorPosFun);
    //glfwSetMouseButtonCallback(window, mouseButtonFun);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    glfwGetFramebufferSize(window, &width, &height);

    scene = new Scene10();
    scene->load();
    
    resizeWindow(window, width, height);

    play();
}

void LittleEngine::Engine::resizeWindow(GLFWwindow* window, int width, int height) 
{
    this->width = width;
    this->height = height;
    scene->resize(width, height);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void LittleEngine::Engine::key(GLFWwindow* window, int k, int s, int action, int mods)
{
    if(action != GLFW_PRESS) return;
    if (k == GLFW_KEY_ESCAPE) {        
        currentState = LittleEngine::EngineState::EXIT;
        return;
    }
    if (k == GLFW_KEY_SPACE) {
        currentState = currentState == LittleEngine::EngineState::PAUSE ? LittleEngine::EngineState::PLAY : LittleEngine::EngineState::PAUSE;
        prevTime = std::chrono::high_resolution_clock::now();
        return;
    }

    InputManager::instance()->key(window, k, s, action, mods);
}

void LittleEngine::Engine::mainLoop() 
{
    glfwGetFramebufferSize(window, &width, &height);
    if (currentState == LittleEngine::EngineState::PLAY) {
        std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
        double elapsed = std::chrono::duration<double>(currentTime - prevTime).count();
        prevTime = currentTime;
        lag += elapsed;

        while (lag >= MS_PER_UPDATE) {
            scene->update(elapsed);
            lag -= MS_PER_UPDATE;
        }
    }
    scene->render();

    glfwSwapBuffers(window);
    glfwPollEvents();
    run();
}

void LittleEngine::Engine::exit() {
    delete scene;
    glfwTerminate();
    std::exit(EXIT_SUCCESS);
}