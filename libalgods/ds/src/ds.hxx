#pragma once

#include <iosfwd>
#include <string>

#include <src/export.hxx>

namespace ds
{
  // Print a greeting for the specified name into the specified
  // stream. Throw std::invalid_argument if the name is empty.
  //
  SRC_SYMEXPORT void
  say_hello (std::ostream&, const std::string& name);
}
