#include "pch.h"
#include "serializers/JSONSerializer.h"

void JsonSerializer::Start(void* document)
{
	_document = static_cast<nlohmann::ordered_json*>(document);
}

void JsonSerializer::SerializeField(const char* name, const std::string& value)
{
	(*_document)[name] = value;
}

void JsonSerializer::SerializeField(const char* name, const int& value)
{
	(*_document)[name] = value;
}
