//#include <string>
import<string>;

template<typename type>
[[nodiscard]] constexpr auto
asString(type string_type) -> auto {
  if constexpr (std::is_same_v<std::string, type>) {
    return string_type;
  } else if constexpr (std::is_arithmetic_v<type>) {
    return std::to_string(string_type);
  } else {
    return std::string{string_type};
  }
}
