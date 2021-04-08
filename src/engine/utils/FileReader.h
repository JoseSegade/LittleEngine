#pragma once
#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <fstream>
#include <streambuf>

namespace LittleEngine 
{
	namespace Utils 
	{
		char* stringFromFile(const char* filePath, unsigned int &length);
	}
}

#endif // !FILEREADER_H_

