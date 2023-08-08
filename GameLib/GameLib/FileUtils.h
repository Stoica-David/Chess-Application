#pragma once

#include <string>

class FileUtils
{
public:
	static bool ReadStringFromFile(const std::string& file, std::string& str);
	static bool WriteStringToFile(const std::string& file, const std::string& str);
};
