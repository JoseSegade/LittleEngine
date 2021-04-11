#include "InputManager.h"
#include <iostream>

void LittleEngine::InputManager::key(GLFWwindow* window, int k, int s, int action, int mods)
{
	for (auto subscriber : subscribers)
	{
		subscriber.second(k, s);
	}
}
