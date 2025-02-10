#pragma once
#include <string>
#include "core/Document.h"

class FileUtils {
public:
	static bool FileUtils::Read(const char* filePath, std::string& content);
	static bool FileUtils::Write(const char* filePath, const char* data);

	static bool FileToDocument(const char* filePath, Document* document);
};