#pragma once
#include "core/Serializer.h"
#include "nlohmann/json.hpp"

class JsonSerializer : public Serializer {
public:
	void Start(void* document) override;
	void SerializeField(const char* name, const std::string& value) override;
	void SerializeField(const char* name, const int& value) override;

private:
	nlohmann::ordered_json* _document;
};
