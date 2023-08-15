#include <src/ds.hxx>

#include <ostream>
#include <stdexcept>

using namespace std;

namespace ds
{
  void say_hello (ostream& o, const string& n)
  {
    if (n.empty ())
      throw invalid_argument ("empty name");

    o << "Hello, " << n << '!' << endl;
  }
}
