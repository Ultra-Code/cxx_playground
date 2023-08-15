//#include <experimental/map>
//#include <iostream>
//#include <mutex>
//#include <string>
//#include <tuple>
//#include <vector>
import "experimental/map";
import<iostream>;
import<mutex>;
import<string>;
import<tuple>;
import<vector>;

template<typename T1, typename T2>
struct Pair3 {
  T1 first;
  T2 second;
  Pair3(const T1 &x, const T2 &y)
      : first{x}
      , second{y} {}
};
template<typename T1, typename T2>
explicit Pair3(T1, T2) -> Pair3<T1, T2>;
template<typename T>
struct String {
  T val;
};
explicit String(const char *)->String<std::string>;
auto
use_main() -> int {
  Pair3 pair3{"Hello", "World"};
  auto S{String{"Hello"}};
  String i{""};
  const char *const string_array[] = {"A", "B", "C"};
  // examples
  // std::complex c{ 3.2, 3.2 };
  // std::mutex mx{};
  // std::lock_guard lock{ mx };
  /*
   *std::vector vec{ 1, 1, 2, 2 };
   *auto veck{ std::vector{ 3, 3 } };
   *std::tuple tuple{ 2, "two", true };
   *std::pair pair{ "", 1 };
   *auto pair2{ std::make_pair(std::string{}, 1) };
   */
}
