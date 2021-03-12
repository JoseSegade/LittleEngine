#pragma once
#ifndef INPUTMANAGER_H_
#define INOUTMANAGER_H_

#include <GLFW\glfw3.h>
namespace LittleEngine {
	class InputManager {
	public:
		static InputManager& instance();
	private:
		InputManager();
	public:
		InputManager(InputManager const&) = delete;
		void operator=(InputManager const&) = delete;
		void key(GLFWwindow* window, int k, int s, int action, int mods);
	};
}

#endif // !INPUTMANAGER_H_