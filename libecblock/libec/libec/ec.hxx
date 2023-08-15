#pragma once

#include <iosfwd>
#include <iostream>
#include <string>

#include <libec/export.hxx>

namespace ec
{
  // Print a greeting for the specified name into the specified
  // stream. Throw std::invalid_argument if the name is empty.
  //
  LIBEC_SYMEXPORT auto say_hello(std::ostream &, const std::string &name)
      -> void;
} // namespace ec
