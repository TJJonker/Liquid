#pragma once
#include "core/ISerializable.h"

class NestedClass : public ISerializable {
public:
	void Serialize(Serializer* serializer) override {
		SERIALIZE(_nestedInteger);
		SERIALIZE(_nestedString);
	}

private:
	int _nestedInteger = 42;
	std::string _nestedString = "Hello World";
};