#include "pch.h"
#include "core/FileUtils.h"

bool FileUtils::Read(const char* filePath, std::string& content)
{
	try {
		std::ifstream fileStream(filePath);
		fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		if (!fileStream.is_open()) {
			return false;
		}

		std::stringstream resultStream;
		resultStream << fileStream.rdbuf();

		content = resultStream.str();
		return true;
	}
	catch (std::ifstream::failure e) {
		return false;
	}
}

bool FileUtils::Write(const char* filePath, const char* data)
{
	try {
		std::ofstream fileStream(filePath, std::ios::out | std::ios::trunc);
		fileStream.exceptions(std::ofstream::failbit | std::ofstream::badbit);

		if (!fileStream.is_open()) {
			return false;
		}

		fileStream << data;
		fileStream.close();

		return true;
	}
	catch (const std::ofstream::failure& e) {
		return false;
	}
}