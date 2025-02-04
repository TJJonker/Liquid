#include "pch.h"
#include "core/FileUtils.h"
#include "temp/ExampleClass.h"
#include "serializers/JSONSerializer.h"

int main() {
	ExampleClass classes[2];

	nlohmann::ordered_json document;
	Serializer* serializer = new JsonSerializer();
	serializer->Initialize(&document);

	SERIALIZECLASSARRAY(classes, 2);

	FileUtils::Write("temp/WriteTest.json", document.dump(4).c_str());
}