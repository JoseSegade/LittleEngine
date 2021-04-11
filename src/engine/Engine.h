#pragma once
#ifndef ENGINE_H_
#define ENGINE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLFW_INCLUDE_NONE
#define MS_PER_UPDATE 0.016

#include <string>
#include <chrono>
#include <iostream>
#include "engine/managers/InputManager.h"
#include "engine/scene/IScene.h"
#include "engine/scene/scenes/Scene4.hpp"

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
