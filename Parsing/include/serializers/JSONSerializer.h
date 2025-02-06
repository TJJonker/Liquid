#pragma once
#include <stack>
#include "core/Serializer.h"
#include "nlohmann/json.hpp"

class JsonSerializer : public Serializer {
public:
	void Initialize(void* document) override;
	void Start() override;
	void End(const char* name) override;
	void AddToArray(const char* name) override;

	void SerializeField(const char* name, const std::string& value) override;
	void SerializeField(const char* name, const int& value) override;

private:
	void IncreaseIndent();
	void DecreaseIndent();

private:
	nlohmann::ordered_json* _document;
	std::stack<nlohmann::ordered_json*> _classStack;
	int _indentLevel;
};
