#include "pch.h"

#include <type_traits>

template <typename T>
struct has_toString {
	template <typename U>
	static auto test(int) -> decltype(std::declval<U>().toString(), std::true_type{});

	template <typename>
	static std::false_type test(...);

public:
	static constexpr bool value = decltype(test<T>(0))::value;
};

int main() {
	struct A { std::string toString() const { return "A"; } };
	struct B {};

	std::cout << has_toString<A>::value << std::endl;  // Should print 1 (true)
	std::cout << has_toString<B>::value << std::endl;  // Should print 0 (false)

}