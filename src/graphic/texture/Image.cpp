#include "Image.h"
#include <stb_image.h>

#include "../../system/console/Console.h"

unsigned char* Image::load(const std::string& path, int* width, int* height, int* channels)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), width, height, channels, 0);
	return data;
}