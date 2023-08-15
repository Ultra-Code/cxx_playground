#include <iostream>
#include <cmath>
#include <cassert>
#include <array>
#include <type_traits>
#include <utility>
#include <string_view>
#include <bit>

template<int size> class int_map
{
  static_assert(size > 0, "size of a map can't be less than 0");
  std::array<int, size> data;

public:
  [[nodiscard]] static constexpr auto
  hash(std::string_view value) -> size_t
  {
    auto hash_result = size_t(0);
    for (constexpr auto small_prime_multipler = uint8_t(37);
         auto const &element : value)
      {
        /// make sure characters are treated as unsigned for modular
        /// operations
        auto const unsigned_value = std::bit_cast<u_char>(element);
        /// hash_result undergoes a modolu 2^64 since hash_result is 64bit
        /// unsigned
        hash_result = hash_result * small_prime_multipler + unsigned_value;
      }
    return hash_result;
  }

  [[nodiscard]] static constexpr auto
  hash(size_t value) -> size_t
  {
    return value % size;
  }

  constexpr auto
  insert(int value) -> void
  {
    data[hash(value)] = value;
  }

  constexpr auto
  find(int value) const -> std::pair<bool, int>
  {
    if (data[hash(value)] == value)
      {
        return { true, data[hash(value)] };
      }
    return { false, -1 };
  }

  constexpr auto
  remove(int value) -> bool
  {
    if (auto const &[found, val] = find(value); found)
      {
        data[value % size] = -1;
        return found;
      }
    return false;
  }
};

namespace algo
{
  using namespace std;

  auto
  is_prime(int number) -> bool
  {
    assert(number > 2 && "prime number can't be less than 2");

    for (int divisor = 2; divisor <= number / 2; ++divisor)
      {
        if (number % divisor == 0)
          {
            return false;
          }
      }
    return true;
  }

  auto
  is_primes(int lower_limit) -> bool
  {
    for (int n = 2; n * n <= lower_limit; ++n)
      {
        if (lower_limit % n == 0)
          {
            return false;
          }
        if (n + 1 > std::sqrt(lower_limit))
          {
            return true;
          }
      }
    return true;
  }

  void
  prime_generator(int lower_limit, int upper_limit)
  {
    assert(lower_limit > 2 && lower_limit < upper_limit
           && "prime number can't be less than 2");
    std::cout << "Here is the list of all the prime numbers Below "
              << upper_limit << '\n';
    // implementing for loop to find out prime numbers
    for (; lower_limit < upper_limit; ++lower_limit)
      {
        if (is_primes(lower_limit))
          {
            std::cout << lower_limit << ' ';
          }
      }
  }

  auto
  range_prime(int lower_limit, int upper_limit)
  {
    assert(lower_limit > 2 && lower_limit < upper_limit
           && "prime number can't be less than 2");
    for (; lower_limit < upper_limit; ++lower_limit)
      {
        if (is_prime(lower_limit))
          {
            cout << lower_limit << ' ';
          }
      }
  }

} // namespace algo

auto
main(int argc, char *argv[]) -> int
{
  /* auto map = int_map<1>();
  map.insert(3);
  auto const &[found, value] = map.find(3);
  found ? std::cout << value << " found \n"
        : std::cout << "sorry " << value << " not found\n";
  map.remove(3) ? std::cout << value << " has been removed\n"
                : std::cout << value << " not found so not removed\n";
  std::cout << "The hash of Bernard  is " << map.hash("Bernard") << '\n';
  std::cout << "The hash of Bernards is " << map.hash("Bernards") << '\n';
  std::cout << "The hash of Assan    is " << map.hash("Assan") << '\n';
  std::cout << "shit 8 << 2 is " << (8 << 2) << '\n';
  std::cout << "shit 8 >> 2 is " << (8 >> 2) << '\n'; */
  algo::prime_generator(3, 1'000'000'000);
  /* algo::is_prime(5) ? std::cout << "is prime \n" : std::cout << "not prime \n";
  algo::range_prime(3, 402); */
}
