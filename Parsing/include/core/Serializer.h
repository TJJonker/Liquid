#pragma once
#include <string>

class Serializer {
public:
	virtual ~Serializer() = default;

	virtual void Start(void* document) = 0;
	virtual void StartClass() = 0;
	virtual void EndClass(const char* name) = 0;

	virtual void SerializeField(const char* name, const std::string& value) = 0;
	virtual void SerializeField(const char* name, const int& value) = 0;
};