#include "pch.h"
#include <type_traits>

template <typename T, std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
void print(T value) {
	std::cout << "something" << std::endl;
}

int main() {
	print(3.14);  // Should compile
	print(42);    // Should NOT compile
}