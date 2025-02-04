#include "pch.h"
#include "core/FileUtils.h"
#include "temp/ExampleClass.h"
#include "serializers/JSONSerializer.h"

int main() {
	ExampleClass exampleClass[2];

	nlohmann::ordered_json document;
	Serializer* serializer = new JsonSerializer();
	serializer->Initialize(&document);

	SERIALIZECLASSARRAY(exampleClass, 2);

	FileUtils::Write("temp/WriteTest.json", document.dump(4).c_str());
}