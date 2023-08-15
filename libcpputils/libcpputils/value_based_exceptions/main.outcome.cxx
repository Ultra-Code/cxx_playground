#include <libcpputils/value_based_exceptions/outcome.generic.hxx>
//#include <fmt/printf.h>
import "fmt/core.h";

[[noreturn]] auto
trys() {
  fmt::print("I am trys\n");
  throw domain::my_generic_status_error_(domain::my_status::failure);
}

auto
main_outcome() -> void {
  try {
    fmt::print("I am hear try\n");
    trys();
  } catch (domain::my_generic_status_error_ static_exceptions) {
    fmt::print("I am hear catch\n");
    fmt::print("Domain {} with message {} \ncode {} \n",
               static_exceptions.code().domain().name().c_str(),
               static_exceptions.what(), static_exceptions.code().value());
  }
}
