#pragma once
#include "core/Serializer.h"
#include "core/StringUtils.h"

#define SERIALIZE(field) \
	serializer->SerializeField(StringUtils::StripStartingUnderscore(#field).c_str(), field);

class ISerializable {
public:
	virtual void Serialize(Serializer* serializer) = 0;
};