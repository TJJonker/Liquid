#include "pch.h"
#include "serializers/JSONSerializer.h"

void JsonSerializer::Initialize(void* document)
{
	_document = static_cast<nlohmann::ordered_json*>(document);
	_classStack.push(_document);
	_indentLevel = 1;
}

void JsonSerializer::Start()
{
    nlohmann::ordered_json* newClass = new nlohmann::ordered_json();
    _classStack.push(newClass);
    IncreaseIndent();
}


void JsonSerializer::End(const char* name)
{
	nlohmann::ordered_json* doc = _classStack.top();
	_classStack.pop();
    (*_classStack.top())[name] = *doc; 
	delete doc;

	DecreaseIndent();
}

void JsonSerializer::AddToArray(const char* name)
{
	nlohmann::ordered_json* doc = _classStack.top();
	_classStack.pop();
	(*_classStack.top())[name].push_back(*doc);
	delete doc;

	DecreaseIndent();
}

void JsonSerializer::SerializeField(const char* name, const std::string& value)
{
	(*_classStack.top())[name] = value;
}

void JsonSerializer::SerializeField(const char* name, const int& value)
{
	(*_classStack.top())[name] = value;
}

void JsonSerializer::IncreaseIndent()
{
	_indentLevel++;
}

void JsonSerializer::DecreaseIndent()
{
	_indentLevel--;
}
