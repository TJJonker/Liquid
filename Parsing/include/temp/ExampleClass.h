#pragma once
#include "core/ISerializable.h"
#include "temp/NestedClass.h"

class ExampleClass : public ISerializable
{
public:
	void Serialize(Serializer* serializer) override {
		SERIALIZE(_something);
		SERIALIZE(_foo);
		SERIALIZECLASS(_nestedClass);
	}	

private:
	int _something = 15;
	std::string _foo = "Bar";
	NestedClass _nestedClass;
};

