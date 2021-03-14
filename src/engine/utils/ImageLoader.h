#pragma once
#ifndef IMAGELOADER_H_
#define IMAGELOADER_H_

#include <lodepng.h>
#include <iostream>
#include "Logger.h"

namespace LittleEngine
{
	namespace Utils
	{
		unsigned char* loadImageFromFile(const char* path, int* width, int* height);
	}
}

#endif // !IMAGELOADER_H_

