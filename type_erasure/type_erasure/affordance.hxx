#include <memory>
namespace type_erasure
{

  struct function_interface
  {
    function_interface() = default;

    function_interface(function_interface const &) = delete;

    auto
    operator=(function_interface const &) -> function_interface & = delete;

    function_interface(function_interface &&) = delete;

    auto
    operator=(function_interface &&) -> function_interface & = delete;

    [[nodiscard]] virtual auto
    clone() const -> std::unique_ptr<function_interface> = 0;

    [[nodiscard]] virtual auto
    call_operator() const -> int
        = 0;

    virtual ~function_interface() = default;
  };

  template<typename func_type> struct function_impl final : function_interface
  {
    func_type type_; // NOLINT

    explicit function_impl(func_type func)
        : type_{ std::move(func) }
    {
    }

    [[nodiscard]] auto
    clone() const -> std::unique_ptr<function_interface> override
    {
      return std::make_unique<function_impl<func_type>>(type_);
    }

    [[nodiscard]] auto
    call_operator() const -> int override
    {
      return type_();
    }
  };

  class function
  {
    std::unique_ptr<function_interface> ptr_ = nullptr;

  public:
    template<typename func_type>
    explicit function(func_type type)
        : ptr_{ std::make_unique<function_impl<func_type>>(std::move(type)) }
    {
    }

    function(function const &rhs_copy)
        : ptr_{ rhs_copy.ptr_->clone() }
    {
    }

    auto
    operator=(function const &rhs_copy) -> function &
    {
      auto copy = rhs_copy;
      std::swap(copy.ptr_, ptr_);
      return *this;
    }

    function(function &&) = default;

    auto
    operator=(function &&) -> function & = default;

    auto
    operator()() const -> int
    {
      return ptr_->call_operator();
    }

    ~function() = default;
  };
} // namespace type_erasure
