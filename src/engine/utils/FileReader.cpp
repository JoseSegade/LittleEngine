#include "FileReader.h"

std::string LittleEngine::Utils::stringFromFile(const char* filePath, unsigned int &length)
{
	std::string ret;
	std::ifstream file(filePath);
	if (!file) return 0;

	file.seekg(0, std::ios::end);
	length = file.tellg();
	ret.reserve(length);
	file.seekg(0, std::ios::beg);

	ret.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

	file.close();

	return ret;
}
