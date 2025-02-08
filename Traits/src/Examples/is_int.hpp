#include "pch.h"

#include <type_traits>

template<typename T>
struct is_int : std::false_type {};

template <>
struct is_int<int> : std::true_type {};

int main() {
	std::cout << std::boolalpha;
	std::cout << is_int<int>::value << std::endl;  // Should print 1 (true)
	std::cout << is_int<double>::value << std::endl;  // Should print 0 (false)
}