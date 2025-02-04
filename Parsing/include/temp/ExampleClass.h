#pragma once
#include "core/ISerializable.h"

template<typename Derived>
class ExampleClass : public ISerializable
{
public:
	std::string GetClassName
	void Serialize(Serializer* serializer) override;

private:
	int _something = 15;
};