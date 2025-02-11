#pragma once
#include "archives/archive.hpp"
#include "nlohmann/json.hpp"

class JSONOutputArchive : public OutputArchive<JSONOutputArchive> {
public:
	JSONOutputArchive() : OutputArchive<JSONOutputArchive>(this) { };

	template<typename T>
	void ProcessImpl(T& data) {

	}

private:
	nlohmann::ordered_json _json;
};