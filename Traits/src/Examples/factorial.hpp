#include "pch.h"
#include <type_traits>

template <int T>
struct factorial {
	static constexpr int value = T * factorial<T - 1>::value;
};

template <>
struct factorial<0> {
	static constexpr int value = 1;
};

int main() {
	std::cout << factorial<5>::value << std::endl;  // Should print 120
	std::cout << factorial<6>::value << std::endl;  // Should print 720
}