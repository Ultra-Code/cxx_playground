#include <cassert>
#include <sstream>
#include <stdexcept>

#include <libec/version.hxx>
#include <libec/ec.hxx>

auto
main() -> int
{
  using namespace std;
  using namespace ec;

  // Basics.
  //
  {
    ostringstream o;
    say_hello (o, "World");
    assert(o.str() == "Hello, World!\n");
  }

  // Empty name.
  //
  try
  {
    ostringstream o;
    say_hello (o, "");
    assert (false);
  }
  catch (const invalid_argument& e)
  {
    assert (e.what () == string ("empty name"));
  }
}
