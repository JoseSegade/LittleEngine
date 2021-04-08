#include "FileReader.h"

char* LittleEngine::Utils::stringFromFile(const char* filePath, unsigned int &length)
{
	std::ifstream file(filePath);
	if (!file) return 0;

	file.seekg(0, std::ios::end);
	length = file.tellg();	
	file.seekg(0, std::ios::beg);

	char* ret = new char[length + 1];
	int i = 0;
	while (file.good())
	{
		ret[i] = char(file.get());
		if (!file.eof())
		{
			++i;
		}
		else
		{
			length = i;
		}
	}

	ret[length] = '\0';

	file.close();

	return ret;
}
