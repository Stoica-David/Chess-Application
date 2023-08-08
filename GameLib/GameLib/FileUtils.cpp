#include "FileUtils.h"

#include <fstream>
#include <sstream>

bool FileUtils::ReadStringFromFile(const std::string& file, std::string& str)
{
	std::ifstream inFile(file);

	if (inFile.is_open())
	{
		std::stringstream buffer;
		buffer << inFile.rdbuf();
		str = buffer.str();
		inFile.close();

		return true;
	}

	return false;
}

bool FileUtils::WriteStringToFile(const std::string& file, const std::string& str)
{
	std::ofstream outFile(file);

	if (outFile.is_open())
	{
		outFile << str;
		outFile.close();

		return true;
	}

	return false;
}