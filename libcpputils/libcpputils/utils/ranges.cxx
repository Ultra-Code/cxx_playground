#include <algorithm>
#include <cassert>
#include <fstream>
//#include <iostream>
//#include <ranges>
// import<fstream>;
import<iostream>;
import<ranges>;
auto
rang() {
  // auto data = std::ranges::istream_view<int>(std::cin) |
  // std::ranges::views::transform([](int i) { return i * 2; });
  auto vector_ints = std::vector<int>(std::istream_iterator<int>(std::cin),
                                      std::istream_iterator<int>());
  return vector_ints;
}

auto
ranges_main() -> int {
  std::cout.imbue(std::locale{""});
  std::vector<int> a;
  a.insert(a.cbegin(), std::istream_iterator<int>(std::cin),
           std::istream_iterator<int>());
  auto &&in = std::ifstream("list1401.in");
  if (not in) {
    std::cerr << "list1401.in: " << std::generic_category().message(errno)
              << '\n';
  } else {
    std::ranges::copy(std::ranges::istream_view<int>(in),
                      std::ostream_iterator<int>(std::cout, "\n"));
    in.close();
  }
}
auto
try_range_views() -> void {

  std::vector<int> data{}; // initialized to be empty
  int input{};

  // Read integers one at a time.
  std::cin.imbue(std::locale());
  while (std::cin >> input) {
    // Store each integer in the vector.
    // data.emplace_back(input);
    std::ranges::copy(std::ranges::istream_view<int>(std::cin),
                      std::back_inserter(data));
  }
  auto &&out_itr = std::ostream_iterator<int>(std::cout, "\n");

  assert(std::isupper('A', std::locale{"en_US.latin1"}) == true);
  assert(std::islower('A', std::locale{"en_US.latin1"}) == false);
  assert(std::isupper(u'Æ', std::locale{"en_US.latin1"}) == true);
  assert(std::islower(u'Æ', std::locale{"en_US.latin1"}) == false);
  assert(std::islower(u'½', std::locale{"en_US.latin1"}) == false);
  assert(std::isupper(u'½', std::locale{"en_US.latin1"}) == false);

  // Sort the vector.
  std::ranges::sort(data);

  // Print the vector, one number per line.
  // for (int element : data)
  //    std::cout << element << '\n';
  std::ranges::copy(data, std::ostream_iterator<int>(std::cout, "\0\t"));
}
