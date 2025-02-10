#pragma once
#include <type_traits>

typedef std::false_type no;
typedef std::true_type yes;

// Base template: assumes that Serialize method doesn't exist
template<typename T, typename = void>
struct is_serializable : no {};

// Specialization: checks if the Serialize method exists for any Archive type
template<typename T>
struct is_serializable<T, std::void_t<
    decltype(std::declval<T>().Serialize(std::declval<int&>()))>> : yes {};