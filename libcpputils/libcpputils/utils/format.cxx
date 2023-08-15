#include <fmt/core.h>
//#include <iostream>
//#include <numeric>
//import "fmt/core.h";
import<iostream>;
import<numeric>;

auto
try_format() -> void {
  for (auto init = uint8_t(1); init != 2; ++init) {
    fmt::print("'{0:c}': {0:#09x} {0:0>#10b} |{0:{1}d}| {2:s}\n", '*', 19,
               "str");
    fmt::print("bits per bool: {} \n", std::numeric_limits<bool>::digits);
  }
  int constexpr low{1};      ///< Minimum value for the table
  int constexpr high{10};    ///< Maximum value for the table
  int constexpr colwidth{7}; ///< Fixed width for all columns
  // First print the header.
  std::cout << fmt::format("{1:>{0}c}|", colwidth, '*');
  for (int i{low}; i <= high; i = i + 1) {
    std::cout << fmt::format("{1:{0}}", colwidth, i);
  }
  std::cout << '\n';
  // Print the table rule by using the fill character.
  std::cout << fmt::format("{2:->{0}}+{2:->{1}}\n", colwidth,
                           (high - low + 1) * colwidth, "");
  // For each row...
  for (int row{low}; row <= high; row = row + 1) {
    std::cout << fmt::format("{1:{0}}|", colwidth, row);
    // Print all the columns.
    for (int col{low}; col <= high; col = col + 1)
      std::cout << fmt::format("{1:{0}}", colwidth, row * col);
    std::cout << '\n';
  }
}
