#pragma once
#ifndef INPUTMANAGER_H_
#define INOUTMANAGER_H_

#include "ISingleton.h"
#include "IPublisher.h"

#include <GLFW\glfw3.h>
namespace LittleEngine 
{
	class InputManager: public ISingleton<InputManager>, public IPublisher
	{
	public:
		void key(GLFWwindow* window, int k, int s, int action, int mods);
		void destroy() override {}
	};
}

#endif // !INPUTMANAGER_H_