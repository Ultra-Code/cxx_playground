//#include <iostream>
//#include <string>
import<iostream>;
import<string>;
struct Data {
  std::string name{};
  double value{};
};

struct MoreData
    : Data
    , std::string {
public:
  bool done{};
  std::string data{};
  auto
  print() const {
    if (empty()) {
      std::cout << "[<undefined>]\n";
    }
    std::cout << '[' << name << ' ' << value << "]\n";
  }

private:
  constexpr static bool state{};
};

auto
make_moredata() {
  Data x{"n", 4};
  MoreData data{{"Assan Bernard", 1}, std::to_string(11.11), true, {}};
  data.print();
  std::cout << std::boolalpha
            << std::is_aggregate_v<decltype(data)> << "  and lamda result is ";
}
