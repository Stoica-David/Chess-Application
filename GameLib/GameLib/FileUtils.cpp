#include "FileUtils.h"

#include <fstream>

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
