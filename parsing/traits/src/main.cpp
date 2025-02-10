#include "pch.h"
#include "core/FileUtils.h"
#include "traits.h"
#include "temp/ExampleClass.h"


int main() {
	std::cout << std::boolalpha;
	std::cout << is_serializable<ExampleClass>::value << std::endl;
}