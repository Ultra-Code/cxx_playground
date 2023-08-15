//#include <experimental/source_loca"ion>
//#include <iostream>
#include <any>
import<iostream>;
// import<any>;
import "experimental/source_location";
auto any_move() noexcept -> void;
auto anys() noexcept -> std::uint8_t;

auto
any_move() noexcept -> void {
  std::any a{};
  std::string s{"See any"};
  a = std::move(s);
  std::cout << "A now contains the moved value of "
            << std::any_cast<std::string &>(a) << '\n';
  // s = std::move(std::any_cast<std::string&>(a)); // move assign string in a
  // to s
}

auto
anys() noexcept -> std::uint8_t {
  std::any a = 4.4;
  std::any b = int{4};
  a          = double{1.1};
  std::any inplace{std::in_place_type<int>,
                   1}; // or use make any or
                       // construct object in constructor
  try {
    constexpr auto dob = double{1.1};
    auto &str = std::any_cast<double &>(a) = 4.1;
    std::cout << "Any Value a is : " << str << " \n";
    auto &ptr = std::any_cast<double &>(b) = dob;
    std::cout << "Any Value b is : " << ptr << " \n";
    auto &in_p = std::any_cast<double &>(inplace);
    std::cout << "Any Value inplace is : " << in_p << " \n";
    return 0;
  } catch (std::bad_any_cast &exception) {
    const auto src_info = std::experimental::source_location::current();
    std::cerr << "EXCEPTION : " << exception.what() << " in func '"
              << __PRETTY_FUNCTION__ << "' of file " << src_info.file_name()
              << '\n';
    std::cerr << "Fixing errors : " << '\n';
    const auto &fixed_inplace = std::any_cast<int &>(inplace);
    std::cout << "Any Value inplace is : " << fixed_inplace << " \n";
    return 1;
  }
}
