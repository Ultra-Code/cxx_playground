#include <bit>
#include <concepts>
#include <cassert>
#include <iostream>
#include <type_erasure/any.hxx>
#include <type_erasure/affordance.hxx>
#include <type_erasure/function_view.hxx>
#include <string>

namespace the_stl_way
{
  auto
  call_function(std::regular_invocable auto function,
                std::integral auto... arg) -> void
  {
    function(arg...);
  }
} // namespace the_stl_way

namespace the_contreatifying_templete
{
  auto
  func(std::regular_invocable auto callable) -> void
  {
    using call_type = decltype(callable);

    void *representation = std::bit_cast<void *>(&callable); // NOLINT

    int (*behavior_when_callable_is_called)(void *)
        = +[](void *representation) {
            return (*static_cast<call_type *>(representation))();
          };

    // NOLINTNEXTLINE
    assert(callable() == behavior_when_callable_is_called(representation));
  };
}; // namespace the_contreatifying_templete

struct call
{
  auto
  operator()() -> int
  {
    return 1;
  };
  static auto
  funcs() -> int
  {
    return 1;
  };
};
auto
god_bless_me() -> int
{
  return 3679;
}
auto
god_you_too_much() -> int
{
  return 5;
}
auto
main() -> int
{
  auto fun_ptr = &call::funcs;
  auto fun_lam_ptr = &call::operator();
  auto god_ptr = &god_bless_me;
  auto god_too_ptr = &god_you_too_much;
  auto func_ref = func::function_ref(fun_ptr);
  auto func_ref_call = func::function_ref(fun_lam_ptr);
  assert(func_ref() == 1);
  assert(func_ref_call(call{}) == 1);
  auto copy_func_ref = func_ref;
  assert(copy_func_ref() == 1);
  auto bless_me = func::function_ref(god_ptr);
  assert(bless_me() == 3679);
  bless_me = god_too_ptr;
  assert(bless_me() == 5);
  auto a = Any_Virtual(6);
  std::cout << a.As<int>() << std::endl;

  a = std::string("oh hi!");
  std::cout << a.As<std::string>() << std::endl;

  Any_Virtual av2 = a;

  auto a2 = Any_VoidPtr(42);
  std::cout << a2.As<int>() << std::endl;

  auto a3 = Any_VoidPtr(a.As<std::string>());
  a2 = a3;
  a2.As<std::string>() += " - again!";
  std::cout << "a2: " << a2.As<std::string>() << std::endl;
  std::cout << "a3: " << a3.As<std::string>() << std::endl;

  a3 = a;
  a3.As<Any_Virtual>().As<std::string>() += " - and yet again!!";
  std::cout << "a: " << a.As<std::string>() << std::endl;
  std::cout << "a3->a: " << a3.As<Any_Virtual>().As<std::string>()
            << std::endl;

  the_stl_way::call_function(
      [](auto... args) { (std::cout << ... << args) << '\n'; }, 1, 2, 3);

  the_contreatifying_templete::func([]() { return 1; });
  auto lamda = +[]() { return 1; };
  auto func = func::function_ref(lamda);

  std::cout << func() << '\n';

  auto funcs = type_erasure::function([] { return 1; });
  std::cout << funcs();
}
