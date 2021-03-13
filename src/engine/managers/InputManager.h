#pragma once
#ifndef INPUTMANAGER_H_
#define INOUTMANAGER_H_

#include "ISingleton.h"

#include <GLFW\glfw3.h>
namespace LittleEngine 
{
	class InputManager: public ISingleton<InputManager> 
	{
	public:
		void key(GLFWwindow* window, int k, int s, int action, int mods);
	};
}

#endif // !INPUTMANAGER_H_