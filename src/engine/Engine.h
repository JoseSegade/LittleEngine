#pragma once
#ifndef ENGINE_H_
#define ENGINE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLFW_INCLUDE_NONE
#define MS_PER_UPDATE 0.032

#include <string>
#include <chrono>
#include <iostream>
#include "engine/managers/InputManager.h"
#include "engine/scene/IScene.h"
#include "engine/scene/scenes/Scene1.hpp"
#include "engine/scene/scenes/Scene2.hpp"
#include "engine/scene/scenes/Scene3.hpp"
#include "engine/scene/scenes/Scene4.hpp"
#include "engine/scene/scenes/Scene5.hpp"
#include "engine/scene/scenes/Scene6.hpp"
#include "engine/scene/scenes/Scene7.hpp"
#include "engine/scene/scenes/Scene9.hpp"
#include "engine/scene/scenes/Scene10.hpp"

namespace LittleEngine 
{
	enum class EngineState 
	{
		LOADING, 
		PLAY, 
		PAUSE, 
		EXIT
	};

	class Engine 
	{
	private:
		GLFWwindow*											window;
		IScene*												scene;
		LittleEngine::EngineState							currentState;
		std::chrono::high_resolution_clock::time_point		prevTime;
		double												lag;

		void resizeWindow	(GLFWwindow* window, int width, int height);
		void key			(GLFWwindow* window, int k, int s, int action, int mods);
		void mouse          (GLFWwindow* window, int button, int action, int mods);
		void mouseMove      (GLFWwindow* window, double xpos, double ypos);
		void mouseScroll    (GLFWwindow* window, double xoffset, double yoffset);
		void mainLoop		();
		void exit			();
	public:
		Engine	(const char* name, int width, int height);
		~Engine	();

		int				width;
		int				height;
		std::string		name;

		void run	();
		void init	();
		void pause	();
		void play	();
		
	};
}

#endif // !ENGINE_H_
