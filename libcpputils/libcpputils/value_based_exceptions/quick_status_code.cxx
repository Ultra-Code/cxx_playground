//#include <fmt/printf.h>
#include <libcpputils/value_based_exceptions/quick_status_code.hxx>
import "fmt/core.h";

[[noreturn]] auto
a()
{
  throw system_error2::status_error<
      system_error2::_quick_status_code_from_enum_domain<
          domain::status_codes_>>(domain::status_codes_::error2);
}

auto
quick_status_main() -> int
{
  try
  {
    a();
  }
  catch (system_error2::status_error<
         system_error2::_quick_status_code_from_enum_domain<
             domain::status_codes_>>
             a)
  {
    fmt::print("execptions from {} domain", a.code().message().c_str());
  }
  // Make a status code of the synthesised code domain for `status_codes_`.
  // Note the unqualified lookup, ADL discovers the status_code() free
  // function.
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 auto v =
      status_code(domain::status_codes_::error2);
  static_assert(v.value() == domain::status_codes_::error2);
  static_assert(v.custom_method() == 42);

  // If you don't need custom methods, just use system_code, all erased
  // status codes recognise quick_status_code_from_enum
  BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE::system_code v2(
      domain::status_codes_::error2);
  assert(v2 == v);

  // If v.success() is true, this is a precondition failure which terminates
  // the program
  BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE::error err = v;
  assert(v2 == err);
  return 0;
}
