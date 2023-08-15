#include <type_traits>
#include <memory>
#include <functional>
#include <bit>

namespace func
{

  template<typename signature> class function_ref;

  template<typename function_ref, typename ret, typename signature,
           typename... args>
  concept fn_ref_invocable = std::conjunction_v<
      std::negation<
          std::is_same<std::remove_cvref_t<signature>, function_ref>>,
      std::conditional_t<std::is_nothrow_invocable_v<signature, args...>,
                         std::is_nothrow_invocable_r<ret, signature, args...>,
                         std::is_invocable_r<ret, signature, args...>>>;

  template<typename ret, typename... args> class function_ref<ret(args...)>
  {
    void *func_rep_ = nullptr;
    using function_t = ret (*)(void *func_rep, args...);
    function_t callable_;

  public:
    function_ref() = delete;

    function_ref(function_ref const &) = default;

    auto
    operator=(function_ref const &) -> function_ref & = default;

    function_ref(function_ref &&) noexcept = default;

    auto
    operator=(function_ref &&) noexcept -> function_ref & = default;

    template<typename signature>
      requires fn_ref_invocable<function_ref, ret, signature, args...>
    constexpr explicit function_ref(signature &&func) noexcept
        : func_rep_{ std::bit_cast<void *>(std::addressof(func)) }
        , callable_{ +[](void *func_rep, args &&...arg) -> ret {
          return std::invoke(
              *std::bit_cast<std::remove_cvref_t<signature> *>(func_rep),
              std::forward<args>(arg)...);
        } }
    {
      if constexpr (std::is_member_function_pointer_v<signature>)
        {
          static_assert(!std::is_null_pointer_v<signature>,
                        "member pointer must not be null");
        }
      else
        {
          assert(std::addressof(func) not_eq nullptr); // NOLINT
        }
    }

    template<typename signature>
      requires fn_ref_invocable<function_ref, ret, signature, args...>
    constexpr auto
    operator=(signature &&func) noexcept -> function_ref &
    {
      auto function = function_ref(std::forward<signature>(func));
      this->swap(function);
      return *this;
    }

    constexpr auto
    operator()(args &&...arg) const noexcept
    {
      return callable_(func_rep_, std::forward<args>(arg)...);
    }

    constexpr void
    swap(function_ref &rhs) noexcept
    {
      std::ranges::swap(this->callable_, rhs.callable_);
      std::ranges::swap(this->func_rep_, rhs.func_rep_);
    }

    constexpr ~function_ref() = default;
  };

  template<typename Signature>
  void
  swap(function_ref<Signature> &lhs, function_ref<Signature> &rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template<typename ret, typename... args>
  function_ref(auto (*)(args...)->ret) -> function_ref<auto(args...)->ret>;

  template<typename ret, typename... args>
  function_ref(auto (*)(args...) noexcept->ret)
      -> function_ref<auto(args...) noexcept->ret>;

  template<typename lamda, typename... args>
    requires requires() { &lamda::operator(); }
  function_ref(lamda)
      ->function_ref<auto(args...)->std::invoke_result_t<lamda, args...>>;

  template<class member_func, typename... args>
    requires requires(member_func func) { member_func(func); }
  function_ref(auto (member_func::*)(args...))
      -> function_ref<auto(member_func &&, args...)
                          ->std::invoke_result_t<member_func, args...>>;

} // namespace func
