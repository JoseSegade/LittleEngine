#pragma once
#ifndef INPUTMANAGER_H_
#define INOUTMANAGER_H_

#include "ISingleton.h"
#include "IPublisher.h"

#include <GLFW\glfw3.h>
namespace LittleEngine 
{
	struct KeyMessage
	{
		int k;
		int s;
	};

	struct MouseMessage
	{
		int button;
		int action;
		double posX;
		double posY;
	};

	struct MouseMoveMessage
	{
		double posX;
		double posY;
	};

	struct MouseScrollMessage
	{
		double offset;
	};

	class InputManager: public ISingleton<InputManager>, public IPublisher
	{
	public:
		void key         (GLFWwindow* window, int k, int s, int action, int mods);
		void mouse       (GLFWwindow* window, int k, int action, int mods, double posX, double posY);
		void mouseMove   (GLFWwindow* window, double xpos, double ypos);
		void mouseScroll (GLFWwindow* window, double xoffset, double yoffset);
		void destroy() override {}
	};
}

#endif // !INPUTMANAGER_H_