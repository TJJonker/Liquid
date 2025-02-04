#pragma once
#include "core/Serializer.h"
#include "core/StringUtils.h"

#define SERIALIZE(field) \
	serializer->SerializeField(StringUtils::StripStartingUnderscore(#field).c_str(), field);

template<typename Derived>
class ISerializable {
public:
	const char* GetClassName() { return typeid(Derived).name(); }
	

	void SerializeClass(Serializer* serializer) 
	{ 
		serializer->StartClass();
		Serialize(serializer);
		serializer->EndClass(GetClassName());
	}

protected:
	virtual void Serialize(Serializer* serializer) = 0;

};