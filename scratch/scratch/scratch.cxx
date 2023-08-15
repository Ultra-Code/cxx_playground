#include <iostream>
#include <string>
#include <cassert>
#include <new>
#include <type_traits>
#include <string>
#include <array>
#include <bit>
template<class T, std::size_t N> class static_vector
{
  // properly aligned uninitialized storage for N T's
  std::array<std::aligned_storage_t<sizeof(T), alignof(T)>, N> data;
  std::size_t m_size = 0;

public:
  // Create an object in aligned storage
  template<typename... Args>
  void
  emplace_back(Args &&...args)
  {
    if (m_size >= N) // possible error handling
      {
        throw std::bad_alloc{};
      }

    // construct value in memory of aligned storage
    // using inplace operator new
    new (std::addressof(data.at(m_size))) T(std::forward<Args>(args)...);
    ++m_size;
  }

  // Access an object in aligned storage
  auto
  operator[](std::size_t pos) const -> const T &
  {
    assert((pos < m_size && "construct an object at pos before accessing it"));
    // note: needs std::launder as of C++17
    return *std::launder(
        std::bit_cast<const T *>(std::addressof(data.at(pos))));
  }

  // Delete objects from aligned storage
  ~static_vector()
  {
    for (std::size_t pos = 0; pos < m_size; ++pos)
      {
        // note: needs std::launder as of C++17
        std::launder(std::bit_cast<T *>(std::addressof(data.at(pos))))->~T();
      }
  }
};

#include <thread>
#include <atomic>
#include <chrono>
auto
main() -> int
{
  /* auto v1 = static_vector<std::string, 10>();
  v1.emplace_back(5, '*');
  v1.emplace_back(10, '*');
  v1.emplace_back(3, '|');
  std::cout << v1[0] << '\n' << v1[1] << '\n' << v1[3] << '\n'; */
  using clock = std::chrono::steady_clock;
  auto const deley = clock::now() + std::chrono::milliseconds(1);
  auto counter = std::atomic_int();

  auto threadA = std::jthread([&] {
    while (clock::now() < deley)
      {
        printf("The value in threadA counter is %d \n", ++counter);
      }
  });
  while (clock::now() < deley)
    {
      printf("The value in main thread counter is %d \n", ++counter);
    }
  threadA.join();
}
