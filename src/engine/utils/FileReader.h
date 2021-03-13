#pragma once
#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <fstream>
#include <string>
#include <streambuf>

namespace LittleEngine 
{
	namespace Utils 
	{
		std::string stringFromFile(const char* filePath, unsigned int &length);
	}
}

#endif // !FILEREADER_H_

