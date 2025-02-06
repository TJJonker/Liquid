#include "pch.h"

#include <type_traits>

int main() {
	std::cout << std::boolalpha; // Changes 0 to false and others to true in output.
	std::cout << "Is int integral? " << std::is_integral<int>::value << std::endl; // Checks if int is an integral
	std::cout << "Is int integral? " << std::is_integral<float>::value << std::endl; // Checks if float is an integral
}