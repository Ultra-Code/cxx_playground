#include <libec/ec.hxx>

#include <ostream>
#include <stdexcept>

using namespace std;

namespace ec
{
    auto
    say_hello(ostream &o, const string &n) -> void
    {
        if (n.empty())
        {
            throw invalid_argument("empty name");
        }

        o << "Hello, " << n << '!' << endl;
    }
} // namespace ec
