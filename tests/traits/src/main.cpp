#include "pch.h"
#include <type_traits>
#include <vector>

template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, 
	std::void_t<decltype(std::begin(std::declval<T&>())), 
				decltype(std::end(std::declval<T&>()))>>
	: std::true_type {};

int main() {
	std::cout << std::boolalpha;

	std::cout << is_iterable<int[5]>::value << std::endl;  // Should print 1 (true)
}