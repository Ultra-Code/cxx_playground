#include <boost/outcome/experimental/status_result.hpp>
namespace outcome = boost::outcome_v2::experimental;

namespace domain {
  class my_generic_domain_;
  using my_generic_status_code_  = outcome::status_code<my_generic_domain_>;
  using my_generic_status_error_ = outcome::status_error<my_generic_domain_>;

  enum class my_status : int {
    success = 0,
    failure = 1,
  };

  class my_generic_domain_ : public outcome::status_code_domain {

  private:
    template<class>
    friend class system_error2::status_code;
    template<class StatusCode>
    friend class outcome::detail::indirecting_domain;
    using base_                            = outcome::status_code_domain;

    constexpr static auto unique_domain_id = 0xc1131bbb77471f3b;

    [[nodiscard]] auto get_my_status_message(my_status value) const noexcept
        -> string_ref;

  public:
    using string_ref = base_::string_ref;
    using value_type = my_status;

    constexpr explicit my_generic_domain_(
        base_::unique_id_type id = unique_domain_id) noexcept
        : base_(id) {}

    constexpr my_generic_domain_(my_generic_domain_ const &) noexcept = default;

    constexpr my_generic_domain_(my_generic_domain_ &&) noexcept      = default;

    constexpr auto operator     =(my_generic_domain_ const &) noexcept
        -> my_generic_domain_ & = default;

    constexpr auto operator     =(my_generic_domain_ &&) noexcept
        -> my_generic_domain_ & = default;

    constexpr static auto get() -> my_generic_domain_ const &;

    [[nodiscard]] auto name() const noexcept -> string_ref final;

    constexpr virtual ~my_generic_domain_() noexcept {}

  protected:
    [[nodiscard]] auto
    _do_failure(outcome::status_code<void> const &code) const noexcept
        -> bool final;

    [[nodiscard]] auto
    _do_equivalent(outcome::status_code<void> const &code,
                   outcome::status_code<void> const &code_equi) const noexcept
        -> bool final;

    [[nodiscard]] auto
    _generic_code(outcome::status_code<void> const &code) const noexcept
        -> outcome::generic_code final;

    [[nodiscard]] auto
    _do_message(outcome::status_code<void> const &code) const noexcept
        -> string_ref final;

    [[noreturn]] auto
    _do_throw_exception(outcome::status_code<void> const &code) const
        -> void final;
  };
  constexpr my_generic_domain_ my_generic_domain_constexpr_instance;

  inline constexpr auto
  my_generic_domain_::get() -> my_generic_domain_ const & {
    return my_generic_domain_constexpr_instance;
  }

  inline auto
  make_status_code(my_generic_status_code_ status) noexcept
      -> outcome::system_code {
    return outcome::make_status_code_ptr(std::move(status));
  }

  inline auto
  make_status_code(my_status status) noexcept -> my_generic_status_code_ {
    return my_generic_status_code_(outcome::in_place, status);
  }
} // namespace domain
