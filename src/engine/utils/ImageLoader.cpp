#include "ImageLoader.h"

unsigned char* LittleEngine::Utils::loadImageFromFile(const char* path, int* width, int* height)
{
	std::vector<unsigned char> image;
	unsigned int w, h;
	unsigned int error = lodepng::decode(image, w, h, path);
	if (error != 0)
	{
		printWarning(("Error at texture loading." + std::string(path) + ". Error: " + std::string(lodepng_error_text(error))).c_str(), __FILE__, __LINE__);
		return nullptr;
	}
	*width = w;
	*height = h;
	return image.data();
}
