#pragma once
#include "core/Serializer.h"
#include "core/StringUtils.h"

// WIP
#define SERIALIZATION(...) \
    void Serialize(Serializer* serializer) override { \
        (SERIALIZE(__VA_ARGS__), ...); \
    } \
    void Deserialize(Serializer* serializer) override { \
        (DESERIALIZE(__VA_ARGS__), ...); \
    }
// END WIP

#define SERIALIZE(field) \
	serializer->SerializeField(StringUtils::StripStringStarting(#field, "_").c_str(), field);

#define SERIALIZECLASS(field) \
	serializer->Start(); \
	field.Serialize(serializer); \
	serializer->End(#field);

#define SERIALIZECLASSARRAY(field, size) \
	for(int i = 0; i < size; i++) {\
		serializer->Start(); \
		field[i].Serialize(serializer); \
		serializer->AddToArray(#field); }
	
#define DESERIALIZE(field) \
	serializer->DeserializeField(StringUtils::StripStringStarting(#field, "_").c_str(), field);

class ISerializable {
public:
	virtual void Serialize(Serializer* serializer) = 0;
};