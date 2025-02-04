#include "pch.h"
#include "core/FileUtils.h"
#include "temp/ExampleClass.h"
#include "serializers/JSONSerializer.h"

int main() {
	ExampleClass exampleClass;

	nlohmann::ordered_json document;
	Serializer* serializer = new JsonSerializer();
	serializer->Start(&document);

	exampleClass.Serialize(serializer);

	FileUtils::Write("temp/WriteTest.json", document.dump(4).c_str());
}