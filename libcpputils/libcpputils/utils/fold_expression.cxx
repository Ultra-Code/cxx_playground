//#include <experimental/source_location>
//#include <iostream>
//#include <span>
//#include <utility>
import<iostream>;
import<span>;
import<utility>;
import "experimental/source_location";

template<typename T, typename... Args>
auto
create(Args &&...args) -> T {
  // forward arg to contructor of T
  return T{std::forward<Args>(args)...};
}

template<typename... type>
decltype(auto)
fold(type... args) {
  static auto foldname = std::experimental::source_location::current();
  ((std::cout << foldname.function_name() << ' ' << ' ' << args << '\n'), ...);
  return (1 + ... + args);
}
template<typename First, typename... Args>
void
print(const First &firstarg, const Args &...args) {
  std::cout << firstarg;
  (std::cout << ... << [](const auto &arg) -> decltype(auto) {
    std::cout << ' ';
    return arg;
  }(args))
      << '\n';
}
// check whether passed types are homogeneous:
template<typename T1, typename... TN>
struct IsHomogeneous {
  static constexpr bool value = (... && std::is_same<T1, TN>::value);
};
// check whether passed arguments have the same type:
template<typename T1, typename... TN>
constexpr auto
isHomogeneous(T1, TN...) -> bool {
  return (... && std::is_same<T1, TN>::value);
}
template<auto Sep = ' ', typename... Args>
void
paramitizedPrint(const Args &...args) {
  (..., [](const auto &arg) { std::cout << arg << Sep; }(args));
  std::cout << '\n';
}
// ”inherit” all function call operators of passed base types:
template<typename... Ts>
class overload : public Ts... {
public:
  using Ts::operator()...;
};
// base types are deduced from passed arguments:
template<typename... Ts>
overload(Ts...) -> overload<Ts...>;
struct visitor {
  auto
  operator()(int i, int j) {}
  auto
  operator()(int i, std::string const &j) {}
  template<class T1, class T2>
  auto
  operator()(T1 const &i, T2 const &j) {}
};

auto
use_folds() {
  /*
   *std::cout << (fold(1, 2, 3, 4, 5)) << '\n';
   *print(1, 2, 3, 4, 5);
   *std::cout << std::boolalpha << IsHomogeneous<int, float, char>::value <<
   *'\n'; std::cout << IsHomogeneous<int, int, int>::value << '\n'; std::cout <<
   *isHomogeneous(1, 1.1, <'_'>'c') << '\n'; std::cout << isHomogeneous(1, 1, 2)
   *<< '\n';
   */
  paramitizedPrint<'_'>(1, 1.1, 1.11);
  auto &&twice =
      overload{[](std::string &s) { s += s; }, [](auto &v) { v *= 2; }};
  auto i = int{1};
  twice(i);
  visitor()(2, " ");
}
