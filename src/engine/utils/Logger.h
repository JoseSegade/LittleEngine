#pragma once
#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>

namespace LittleEngine 
{
	namespace Utils
	{
		void printWarning(const char* string, const char* file, int line);
	}
}

#endif // !LOGGER_H_

