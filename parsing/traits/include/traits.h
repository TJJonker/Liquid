#pragma once
#include <type_traits>

// Base template: assumes that Serialize method doesn't exist
template<typename T, typename = void>
struct is_serializable : std::false_type {};

// Specialization: checks if the Serialize method exists for any Archive type
template<typename T>
struct is_serializable<T, std::void_t<
    decltype(std::declval<T>().Serialize(std::declval<int&>()))>> : std::true_type {};