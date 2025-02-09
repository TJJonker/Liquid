#include "pch.h"
#include <type_traits>

template <typename T>
struct remove_pointer {
	using type = T;
};

template <typename T>
struct remove_pointer<T*> {
	using type = T;
};

int main() {
	std::cout << std::boolalpha;

	using T = remove_pointer<int*>::type;
	std::cout << std::is_same<T, int>::value << std::endl;

	using D = remove_pointer<float*>::type;
	std::cout << std::is_same<D, int>::value << std::endl;
}