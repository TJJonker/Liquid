#pragma once
#include "core/ISerializable.h"

class ExampleClass : public ISerializable<ExampleClass>
{
protected:
	void Serialize(Serializer* serializer) override;

private:
	int _something = 15;
	std::string _foo = "Bar";
};