//#include <array>
#include <fmt/core.h>
#include <regex>
import<array>;
//  import<regex>;
// import "fmt/core.h";

auto
regex_in_str() -> void {
  fmt::print("In the regex_in_str func \n");
  auto const &&txt_regex               = std::regex(R"_([a-z]+\.txt)_");
  constexpr auto no_regex_alternatives = uint32_t(5);
  std::array<std::string, no_regex_alternatives> fnames = {
      "foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt"};
  for (std::smatch base_match{}; auto const &name : fnames) {
    fmt::print("name {} in loop \n", name);
    if (std::regex_match(name, base_match, txt_regex) == true) {
      fmt::print("found a match \n");
      if (!base_match.empty()) {
        fmt::print("name {} matches regex {} \n", name, base_match[0].str());
      }
    }
  }
}
