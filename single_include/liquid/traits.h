#pragma once
#include <type_traits>

namespace Liquid::traits {

    using no = std::false_type;
    using yes = std::true_type;

#pragma region Serialization Check


    template<typename T, typename = void>
    struct is_serializable : no {};

    template<typename T>
    struct is_serializable<T, std::void_t<
        decltype(std::declval<T>().Serialize(std::declval<int&>()))>> : yes {};

    template<typename T>
    constexpr bool is_serializable_v = is_serializable<T>::value;

#pragma endregion

    #define LIQUID_MAKE_MEMBER_TEST(functionName)                                                                               \
    namespace detail {                                                                                                          \
        template<class T, class A>                                                                                              \
        struct has_archive_##functionName##_impl {                                                                               \
        template <class TT, class AA>                                                                                           \
        static auto test(int) -> decltype(Save(std::declval<AA&>(), std::declval<TT&>()), yes());                               \
        template<class, class>                                                                                                  \
        static no test(...);                                                                                                    \
        static const bool value = decltype(test<T, A>(0))::value;                                                               \
        };                                                                                                                      \
    }                                                                                                                           \
    template<class T, class A>                                                                                                  \
    struct has_archive_save : std::integral_constant<bool, detail::has_archive_save_impl<T, A>::value> {};

    LIQUID_MAKE_MEMBER_TEST(save);
}