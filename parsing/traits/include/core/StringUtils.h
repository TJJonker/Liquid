#pragma once
#include <string>

class StringUtils {
public:
	static std::string StripStringStarting(const std::string& string, const std::string& removeString) {
		return (string.rfind(removeString, 0) == 0) ? string.substr(removeString.length()) : string;
	}
};