//#include <charconv>
//#include <iostream>
//#include <optional>
//#include <string>
//#include <string_view>
#include <initializer_list>
import<charconv>;
import<iostream>;
import<optional>;
import<string_view>;
import<string>;
// import<initializer_list>;

auto
as_int(std::string_view view) -> std::optional<int> {
  int &&view_int{};
  auto &&[ptr, error_code] =
      std::from_chars(view.begin(), view.end(), view_int);
  if (error_code != std::errc{}) {
    return std::nullopt;
  }
  return view_int;
}

auto
process_int() -> void {
  for (auto &&s : {"42", " 077", "hello", "0x33"}) {
    // try to convert s to int and print the result if possible:
    std::optional<int> oi = as_int(s);
    if (oi.has_value()) {
      std::cout << "convert ' " << s << " ' to int: " << oi.value() << "\n";
    } else {
      std::cout << "can ' t convert ' " << s << " ' to int\n";
    }
  }
}
