#include "pch.h"
#include <type_traits>

template<typename T>
struct is_pointer : std::is_pointer<T> {};

int main() {
	std::cout << std::boolalpha;
	std::cout << is_pointer<int*>::value << std::endl;  // Should print 1 (true)
	std::cout << is_pointer<int>::value << std::endl;   // Should print 0 (false)
}