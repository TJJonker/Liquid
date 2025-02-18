#pragma once
#include <type_traits>

namespace Liquid {

    typedef std::false_type no;
    typedef std::true_type yes;

    template<typename T>
    using enable_if_arithmetic_t = std::enable_if_t<std::is_arithmetic_v<T>, int>;

#pragma region Serialization Check

    // Fallback template for serialization check
    template<typename T, typename = void>
    struct is_serializable : no {};

    // Specialization: Serialization check
    template<typename T>
    struct is_serializable<T, std::void_t<
        decltype(std::declval<T>().Serialize(std::declval<int&>()))>> : yes {};

    // Shortcut Serialization Value
    template<typename T>
    constexpr bool is_serializable_v = is_serializable<T>::value;

#pragma endregion
}