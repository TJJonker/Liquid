#pragma once
#include <string>

class StringUtils {
public:
	static std::string StripStartingUnderscore(const std::string& string) {
		return (string[0] == '_') ? string.substr(1) : string;
	}
};