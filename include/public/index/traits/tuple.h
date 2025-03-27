#pragma once

#include <tuple>

#include "template.h"

namespace index {
template <typename T, typename Tuple>
struct tuple_contain;

template <typename T>
struct tuple_contain<T, std::tuple<>> : std::false_type {};

template <typename T, typename U, typename... Ts>
struct tuple_contain<T, std::tuple<U, Ts...>>
    : tuple_contain<T, std::tuple<Ts...>> {};

template <typename T, typename... Ts>
struct tuple_contain<T, std::tuple<T, Ts...>> : std::true_type {};

template <template <typename...> typename T, typename Tuple>
struct tuple_contain_template;

template <template <typename...> typename T>
struct tuple_contain_template<T, std::tuple<>> : std::false_type {};

template <template <typename...> typename T, typename U, typename... Ts>
struct tuple_contain_template<T, std::tuple<U, Ts...>>
    : tuple_contain_template<T, std::tuple<Ts...>> {};

template <template <typename...> typename T, typename... Ts, typename... Temps>
struct tuple_contain_template<T, std::tuple<T<Temps...>, Ts...>>
    : std::true_type {};

template <template <typename...> typename T, typename Tuple>
struct tuple_template_index {};

template <template <typename...> typename T, typename U, typename... Args>
struct tuple_template_index<T, std::tuple<U, Args...>> {
    static constexpr int index_internal() {
        if constexpr (is_template_of<T, U>::value) {
            return 0;
        } else {
            return 1 + tuple_template_index<T, std::tuple<Args...>>::index();
        }
    }
    static constexpr int index = index_internal();
};
}  // namespace index