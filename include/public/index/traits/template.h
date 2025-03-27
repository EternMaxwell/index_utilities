#pragma once

namespace index {
template <template <typename...> typename Template, typename T>
struct is_template_of : std::false_type {};

template <template <typename...> typename Template, typename... Args>
struct is_template_of<Template, Template<Args...>> : std::true_type {};
}