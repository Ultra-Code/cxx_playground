#include <boost/outcome/experimental/status-code/system_error2.hpp>

// This is some third party enumeration type in another namespace
namespace domain {
  // "Initialiser list" custom status code domain
  enum class status_codes_ : size_t { success1, goaway, success2, error2 };
} // namespace domain

// To synthesise a custom status code domain for `status_codes_`, inject the
// following template specialisation:
BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN
template<>
struct quick_status_code_from_enum<domain::status_codes_>
    : quick_status_code_from_enum_defaults<domain::status_codes_> {
  // Text name of the enum
  static constexpr const auto domain_name = "Another Code";

  // Unique UUID for the enum. PLEASE use
  // https://www.random.org/cgi-bin/randbyte?nbytes=16&format=h
  static constexpr const auto domain_uuid =
      "{be201f65-3962-dd0e-1266-a72e63776a42}";

  // Map of each enum value to its text string, and list of semantically
  // equivalent errc's
  static const std::initializer_list<mapping> &
  value_mappings() {
    static const std::initializer_list<mapping> v = {
        // Format is: { enum value, "string representation", { list of errc
        // mappings ... } }
        {domain::status_codes_::success1, "Success 1", {errc::success}}, //
        {domain::status_codes_::goaway,
         "Go away",
         {errc::permission_denied}},                                     //
        {domain::status_codes_::success2, "Success 2", {errc::success}}, //
        {domain::status_codes_::error2,
         "Error 2",
         {errc::function_not_supported}}, //
    };
    return v;
  }

  // Completely optional definition of mixin for the status code synthesised
  // from `Enum`. It can be omitted.
  template<class Base>
  struct mixin : Base {
    using Base::Base;

    // A custom method on the synthesised status code
    constexpr int
    custom_method() const {
      return 42;
    }
  };
};
BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END

// If you wish easy manufacture of status codes from status_codes_:
namespace domain {
  // ADL discovered, must be in same namespace as status_codes_
  constexpr inline BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE::
      quick_status_code_from_enum_code<domain::status_codes_>
      status_code(status_codes_ c) {
    return c;
  }
} // namespace domain
