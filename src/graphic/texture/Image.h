#pragma once
#include <string>

namespace Image
{
	unsigned char* load(const std::string& path, int* width, int* height, int* channels);
};