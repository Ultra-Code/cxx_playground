#include <cstdint>
#include <iostream>
#include <concepts>
#include <string_view>
#include <type_traits>

using std::cout;
template<typename T>
concept ComparableAndCopyable
    = std::three_way_comparable<T> && std::copyable<T>;

// Same types
template<ComparableAndCopyable T>
auto
max(T a, T b) -> T
{
  // if b < a then yield a else yield b
  return b < a ? a : b;
}

// Default Argument
template<typename T = std::string_view>
auto
view(T str = "String View") -> T
{
  return str;
}

template<typename T> class Stack
{
  auto
  printOn(std::ostream &strm) const -> void
  {
  }

  friend auto
  operator<<(std::ostream &strm, Stack<T> const &s) -> std::ostream &
  {
    s.printOn(strm);
    return strm;
  }
};

template<> class Stack<int>
{
  auto
  printOn(std::ostream &strm) -> void
  {
  }
};
// partial specialization of class Stack<> for pointers:
template<typename T> class Stack<T *>
{
  void
  push(T *); // push element
  auto
  pop() -> T *; // pop element
  auto
  top() const -> T *; // return top element
  [[nodiscard]] auto
  empty() const -> bool;
};

// Defirent types
/* template<typename return_type, typename arg1, typename arg2>
auto
max(arg1 a, arg2 b) -> return_type
{
  return b < a ? a : b;
} */

// auto deduced return type
/* template<typename T1, typename T2>
auto
max(T1 a, T2 b) -> auto
{
  return b < a ? a : b;
} */

// pre c++14 deduced return type
/* template<typename T1, typename T2>
auto
max(T1 a, T2 b) -> std::decay_t<decltype(b < a ? a : b)>
{
  return b < a ? a : b;
} */

// return type as a common type
// std::common_type<>::type yields the “common type” of two (or more) dif
// erent types
template<typename T1, typename T2>
auto
max(T1 a, T2 b) -> std::common_type_t<T1, T2>
{
  return b < a ? a : b;
}

template<typename type> class MemberType
{
  using types = int;
};

template<typename type> using MemberType_t = typename MemberType<type>::types;

#include <vector>
template<typename T> class StackArgumentDeduction
{
private:
  std::vector<T> elems; // elements
public:
  StackArgumentDeduction() = delete;
  explicit StackArgumentDeduction(
      T const &elem) // initialize stack with one element
      : elems({ elem })
  {
  }
};
StackArgumentDeduction(char const *)->StackArgumentDeduction<std::string_view>;

// Aggregate template
template<typename type> struct ValueWithComment
{
  type value;
  char const *comment;
};
template<typename type>
ValueWithComment(type, char const *) -> ValueWithComment<type>;

template<auto VAT> // ERROR: floating-point values are not
auto
process(double v) -> double //        allowed as template parameters
{
  return v * VAT;
}

template<char const *str>
auto
see_str() -> char const *
{
  return str;
}
// pass reference to non-type template parameter
template<decltype(auto) N> class C
{
};

int i{};
C<(i)> x;
auto
sum(auto... args)
{
  return (... + args);
}

auto
traverse(auto *root, auto *...paths) -> auto *
{
  return (root->*...->*paths);
}
auto
print(auto... args)
{
  (cout << ... << args) << ' ';
  /* [&args](std::ostream &stream = cout) -> std::ostream & {
  return stream <<' '<< args ;
}); */
}

template<typename type> class Array
{
};
template<typename type, typename... types>
  requires(std::is_same_v<type, types> &&...)
Array(type arg, types... args)
->Array<int>;

template<typename T> class MyClass
{
public:
  void
  foo()
  {
    using ptr = typename T::SubType *;
  }
};

template<typename T> class Base
{
public:
  void
  bar();
};
template<typename T> class Derived : Base<T>
{
public:
  void
  foo()
  {
    Base<T>::bar(); // calls external bar() or error
  }
};
#include <bitset>
template<uint64_t N>
void
printBitset(std::bitset<N> const &bs)
{
  std::cout << bs.template to_string<char, std::char_traits<char>,
                                     std::allocator<char>>();
}

#include <tuple>
struct S
{
  static constexpr auto
  value()
  {
    return std::make_tuple(101, 202);
  }
};
// constexpr arguments
constexpr void
f(auto constexpr_argument)
{
  static_assert(std::get<0>(constexpr_argument()) == 101,
                "constexpr argument isn't equal to 101");
  static_assert(std::get<1>(constexpr_argument()) == 202,
                "constexpr argument isn't equal to 202");
}

// NOLINTNEXTLINE
#define CONSTEXPR_ARG(arg) [] { return arg; }

auto
main() -> int
{
  f(CONSTEXPR_ARG(std::make_tuple(101, 202)));
  cout << ::max("hello", "hello bernard");
  cout << ::max<double>(4.4, 4);
  cout << view();
  // auto inStack = StackArgumentDeduction("hello");
  using std::string_view_literals::operator""sv;
  auto str = StackArgumentDeduction("hello");
  auto valuable_comment
      = ValueWithComment<int>{ .value = 1, .comment = "hello" };
  auto val = ValueWithComment{ 1, "hello" };
  cout << process<3>(2);
  static char const s17[] = "See str in motion"; // no linkage
  cout << see_str<s17>();
  print(1, "hello", 5.2);
  //  Array(1, 1, 3, 3, 4);
}
