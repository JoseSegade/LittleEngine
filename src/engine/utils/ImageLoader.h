#pragma once
#ifndef IMAGELOADER_H_
#define IMAGELOADER_H_

#include <lodepng.h>
#include <vector>
#include <iostream>
#include "Logger.h"

namespace LittleEngine
{
	namespace Utils
	{
		std::vector<unsigned char> loadImageFromFile(const char* path, int* width, int* height);
	}
}

#endif // !IMAGELOADER_H_

