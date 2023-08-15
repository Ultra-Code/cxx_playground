//#include <type_traits>
//#include <iostream>
import<type_traits>;
import<iostream>;
constexpr auto square =
    []<typename T>(T x) constexpr requires std::is_integral_v<T> {
  return x * x;
};

auto
use_square() {
  std::cout << square(2);
}
