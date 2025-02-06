#include "pch.h"

#include <type_traits>

//template <typename T>
//class has_serialize {
//	template <typename U>
//	static auto test(int) -> decltype(std::declval<U>().serialize(), std::true_type{});
//
//	template <typename>
//	static std::false_type test(...);
//
//public:
//	static constexpr bool value = decltype(test<T>(0))::value;
//};
//
//struct A {
//	void serialize() { std::cout << "Serializing A..." << std::endl; }
//};
//
//struct B { };

template <typename T>
struct DefaultType {
	using type = double;
};

template <>
struct DefaultType<int> {
	using type = float;
};

int someting = 0;

int main() {
	//std::cout << std::boolalpha; // Changes 0 to false and others to true in output.
	std::cout << typeid(DefaultType<char>::type).name() << std::endl;
	std::cout << typeid(DefaultType<float>::type).name() << std::endl;
	std::cout << typeid(DefaultType<int>::type).name() << std::endl;
	
	// std::cout << "Does A have serialize()? " << has_serialize<A>::value << std::endl;
	// std::cout << "Does B have serialize()? " << has_serialize<B>::value << std::endl;
}