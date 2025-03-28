#pragma once

#include <functional>
#include <typeindex>
#include <variant>

namespace index {
template <typename... Ts>
struct matcher {
    using Ts::operator()...;
};
template <typename... Ts>
matcher(Ts...) -> matcher<Ts...>;

template <typename... Ts>
auto&& match(std::variant<Ts...>& variant, Ts&&... ts) {
    return std::visit(matcher{std::forward<Ts>(ts)...}, variant);
}
template <typename... Ts, typename... Ms>
auto&& match(std::variant<Ts...>& variant, const matcher<Ms...>& m) {
    return std::visit(m, variant);
}
}  // namespace index