#include "InputManager.h"
#include <iostream>

void LittleEngine::InputManager::key(GLFWwindow* window, int k, int s, int action, int mods)
{
	KeyMessage key;
	key.k = k;
	key.s = s;
	for (auto subscriber : subscribers)
	{
		subscriber.second(&key, typeid(KeyMessage).hash_code());
	}
}

void LittleEngine::InputManager::mouse(GLFWwindow* window, int k, int action, int mods, double posX, double posY)
{
	MouseMessage mouse;
	mouse.button = k;
	mouse.action = action;
	mouse.posX = posX;
	mouse.posY = posY;
	for (auto subscriber : subscribers)
	{
		subscriber.second(&mouse, typeid(MouseMessage).hash_code());
	}
}

void LittleEngine::InputManager::mouseMove(GLFWwindow* window, double xpos, double ypos)
{
	MouseMoveMessage mouse;
	mouse.posX = xpos;
	mouse.posY = ypos;
	for (auto subscriber : subscribers)
	{
		subscriber.second(&mouse, typeid(MouseMoveMessage).hash_code());
	}
}

void LittleEngine::InputManager::mouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	MouseScrollMessage mouse;
	mouse.offset = yoffset;
	for (auto subscriber : subscribers)
	{
		subscriber.second(&mouse, typeid(MouseScrollMessage).hash_code());
	}
}
