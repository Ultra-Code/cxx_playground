#pragma once

#include <iosfwd>
#include <string>

#include <libcpputils/functional/export.hxx>

namespace functional
{
  // Print a greeting for the specified name into the specified
  // stream. Throw std::invalid_argument if the name is empty.
  //
  FUNCTIONAL_SYMEXPORT void
  say_hello(std::ostream &, const std::string &name);
} // namespace functional
