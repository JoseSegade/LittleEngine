#pragma once
#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <glm/glm.hpp>

namespace LittleEngine 
{
	namespace Utils
	{
		void printWarning(const char* string, const char* file, int line);
		void printMat4(const glm::mat4 mat);
	}
}

#endif // !LOGGER_H_

