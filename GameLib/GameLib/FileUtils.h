#pragma once

#include <string>

class FileUtils
{
public:
	static bool WriteStringToFile(const std::string& file, const std::string& str);
};