#pragma once
#include "core/Serializer.h"
#include "core/StringUtils.h"

#define SERIALIZE(field) \
	serializer->SerializeField(StringUtils::StripStringStarting(#field, "_").c_str(), field);

template<typename Derived>
class ISerializable {
public:
	std::string GetClassName() 
	{ 
		return StringUtils::StripStringStarting(typeid(Derived).name(), "class ");
	}
	

	void SerializeClass(Serializer* serializer) 
	{ 
		serializer->StartClass();
		Serialize(serializer);
		serializer->EndClass(GetClassName().c_str());
	}

protected:
	virtual void Serialize(Serializer* serializer) = 0;

};