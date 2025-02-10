#pragma once
#include <string>

class Serializer {
public:
	virtual ~Serializer() = default;

	virtual void Initialize(void* document) = 0;
	virtual void Start() = 0;
	virtual void End(const char* name) = 0;
	virtual void AddToArray(const char* name) = 0;

	virtual void SerializeField(const char* name, const std::string& value) = 0;
	virtual void SerializeField(const char* name, const int& value) = 0;
};