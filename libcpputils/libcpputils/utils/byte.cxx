//#include <bitset>
//#include <cstddef>
//#include <iostream>
//#include <numeric>
import<bitset>;
import<cstddef>;
import<iostream>;
import<numeric>;

auto bytes() -> void;
auto
bytes() -> void {
  constexpr std::byte by{0b1111'0000};
  constexpr std::byte by2{0x3F};
  // bitset takes number of bits as a
  // argument which for an unsigned char
  // its 8
  std::bitset<8ULL> bits_for_output{std::to_integer<unsigned char>(by2)};
  std::cout << std::boolalpha << std::to_integer<bool>(by) << '\n';
  std::cout << bits_for_output << ' '
            << std::numeric_limits<unsigned char>::digits << '\n';
}
