//#include <complex>
//#include <iostream>
#include <optional>
//#include <set>
//#include <string>
import<complex>;
import<iostream>;
// import<optional>;
import<set>;
import<string>;
using std::optional, std::string, std::set;

auto
optionals() {
  [[maybe_unused]] const optional opt_one{1};
  [[maybe_unused]] const optional opt_two{string{"string"}};
  const optional<string> opt_three{std::in_place, "inplace"};
  const auto &sc = [](int x, int y) { return std::abs(x) < std::abs(y); };
  const optional<set<int, decltype(sc)>> opt_four{std::in_place, {1, 1, 1}, sc};
  [[maybe_unused]] const auto &&opt_make_five =
      std::make_optional<set<int, decltype(sc)>>({1, 1}, sc);
  const auto &&sets = std::set{"my", "beautiful", "set"};
  const auto &&opt_six =
      (sets.contains("my") ? std::optional{sets.find("my")} : std::nullopt);
  std::cout << *opt_six.value() << '\n';
}
auto
optional_bool_ptr() {
  /**
   * @brief How optionals with bool and pointers behave
   *
   */
  constexpr optional boolean{false};
  if constexpr (boolean.has_value()) {
    std::cout << std::boolalpha << "func has_value() " << boolean.value()
              << '\n';
  }
  if constexpr (boolean) {
    std::cout << "func implicit convert to boolean .NB:same as above "
              << *boolean << '\n';
  }
  if constexpr (boolean == false) {
    std::cout << "implicit convert boolean to value and compare with false "
              << *boolean << '\n';
  }
  if constexpr (!(*boolean)) {
    std::cout
        << "implicit convert boolean to value and invert .NB:same as above "
        << *boolean << '\n';
  }
}
auto
nested_optionals() {
  std::optional<std::optional<std::string>> oos1;
  std::optional<std::optional<std::string>> oos2 = "hello";
  std::optional<std::optional<std::string>> oos3{std::in_place, std::in_place,
                                                 "hello"};
  std::optional<std::optional<std::complex<double>>> ooc{
      std::in_place, std::in_place, 4.2, 5.3};
  oos1 = "hello"; // OK: assign new value
  ooc.emplace(std::in_place, 7.2, 8.3);
  ooc.emplace().emplace(3.4, 3.3);
  *oos1 = std::nullopt; // inner optional has no value
  oos1  = std::nullopt; // outer optional has no value
  if (!oos1.has_value()) {
    std::cout << "no outer value\n";
  }
  if (oos1 && !(oos1.has_value()) /*same as !*oos1 or !(*oos1) */) {
    std::cout << "no inner value\n";
  }
  if (oos1.has_value() && oos1.value().has_value() /* same as *oos1 */) {
    std::cout << "value: " << **oos1 << '\n';
  }
}
