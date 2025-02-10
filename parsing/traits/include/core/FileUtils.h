#pragma once
#include <string>

class FileUtils {
public:
	static bool FileUtils::Read(const char* filePath, std::string& content);
	static bool FileUtils::Write(const char* filePath, const char* data);
};