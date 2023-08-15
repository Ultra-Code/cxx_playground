#include <libcpputils/value_based_exceptions/outcome.generic.hxx>

namespace domain {

  inline auto
  my_generic_domain_::name() const noexcept -> my_generic_domain_::string_ref {
    return my_generic_domain_::string_ref("my generic custome domain");
  }

  auto
  my_generic_domain_::_do_failure(
      outcome::status_code<void> const &code) const noexcept -> bool {
    assert(code.domain() == *this);                           // NOLINT
    return static_cast<my_generic_status_code_ const &>(code) // NOLINT
               .value() != my_status::success;
  }

  auto
  my_generic_domain_::_do_equivalent(
      outcome::status_code<void> const &code,
      outcome::status_code<void> const &code_equi) const noexcept -> bool {
    assert((code.domain() == *this && code_equi.domain() == *this) ||
           (code_equi.domain() == outcome::generic_code_domain));

    auto const &code_domain =
        static_cast<my_generic_status_code_ const &>(code); // NOLINT

    if (code.domain() == *this && code_equi.domain() == *this) {
      auto const &code_equi_domain =
          static_cast<my_generic_status_code_ const &>( // NOLINT
              code_equi);

      return code_domain.value() == code_equi_domain.value();
    }
    if (code.domain() == *this &&
        code_equi.domain() == outcome::generic_code_domain) {
      auto const &code_equi_domain =
          static_cast<outcome::generic_code const &>(code_equi); // NOLINT
      return static_cast<outcome::errc>(code_domain.value()) ==
             code_equi_domain.value();
    }
    return false;
  }

  auto
  my_generic_domain_::_generic_code(outcome::status_code<void> const &code)
      const noexcept -> outcome::generic_code {
    assert(code.domain() == *this); // NOLINT
    auto const &generic_code_ =
        static_cast<my_generic_status_code_ const &>(code); // NOLINT
    auto const generic_code_errc =
        static_cast<outcome::errc>(generic_code_.value());
    return outcome::generic_code(generic_code_errc);
  }

  auto
  my_generic_domain_::_do_message(
      outcome::status_code<void> const &code) const noexcept -> string_ref {
    assert(code.domain() == *this); // NOLINT

    auto const &code_message =
        static_cast<my_generic_status_code_ const &>(code); // NOLINT
    return get_my_status_message(code_message.value());
  }

  auto
  my_generic_domain_::get_my_status_message(my_status value) const noexcept
      -> string_ref {
    switch (value) {
    case value_type::success: {
      return string_ref("The operation way successfull");
    }
    case value_type::failure: {
      return string_ref("Operation Unsuccessfull");
    }
    }
    return string_ref("");
  }

  auto
  my_generic_domain_::_do_throw_exception(
      outcome::status_code<void> const &code) const -> void {
    assert(code.domain() == *this); // NOLINT

    auto const &code_exception =
        static_cast<my_generic_status_code_ const &>(code); // NOLINT

    throw my_generic_status_error_(code_exception);
  }

} // namespace domain
