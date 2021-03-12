#include "InputManager.h"
#include <iostream>

LittleEngine::InputManager::InputManager()
{
}

LittleEngine::InputManager& LittleEngine::InputManager::instance()
{
	static InputManager instance;
	return instance;
}

void LittleEngine::InputManager::key(GLFWwindow* window, int k, int s, int action, int mods)
{
	std::cout << "Hello" << "\n";
}
