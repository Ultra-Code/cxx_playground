import<array>;
import<complex>;
import<iostream>;
import<set>;
import<string>;
import<variant>;
import<vector>;

//#include <variant>

using std::variant, std::cout, std::string, std::set, std::complex,
    std::vector;
auto
variants() noexcept -> void;
auto
variant_class_derived() noexcept;
auto
variants() noexcept -> void
{
  variant<int, double> var{};
  cout << var.index() << '\n';
  var = 2;
  try
    {
      cout << "index : " << var.index() << '\n';
      const auto &floats = std::get<int>(var);
      cout << "Value of double in variant alternatives is : " << floats
           << '\n';
    }
  catch (const std::bad_variant_access &exception)
    {
      cout << "EXCEPTION :" << exception.what() << '\n';
    }
}
auto
variant_class_derived() noexcept
{
  [[maybe_unused]] std::variant<int, double> v4 = double{ 42.3 };
  class Derived : public std::variant<int, std::string>
  {
  };
  Derived d = { { "hello" } };
  std::cout << d.index() << '\n';      // prints: 1
  std::cout << std::get<1>(d) << '\n'; // prints: hello
  d.emplace<0>(77);                    // initializes int, destroys string
  std::cout << std::get<0>(d) << '\n'; // prints: 77
}
auto
nested_variants() noexcept
{
  [[maybe_unused]] const variant<set<string>> var_set{
    std::in_place_index<0>,
    set{ string{ "Hello" }, string{ "Hello" }, string{ "Hello" } }
  };
  [[maybe_unused]] const variant<std::complex<double>> douvar{
    std::in_place_type<complex<double>>, 4.3
  };
  [[maybe_unused]] const variant<std::array<string, 2>> var_array{
    std::in_place_type<std::array<string, 2>>,
    std::array{ string{ "Arrary" }, string{ "Works" } }
  };
  // initialize variant with a set with lambda as sorting criterion:
  auto sc = [](int x, int y) { return std::abs(x) < std::abs(y); };
  std::variant<std::vector<int>, std::set<int, decltype(sc)>> v15{
    std::in_place_index<1>, { 4, 8, -7, -2, 0, 5 }, sc
  };
}
auto
variant_empty_state() noexcept
{
  variant<std::monostate, int, double> variant_two{};
  cout << "index of variant_two : " << variant_two.index() << '\n';
  if (variant_two.index() == 0)
    {
      cout << "Monostate" << '\n';
    }
  if (std::holds_alternative<std::monostate>(variant_two))
    {
      cout << "Monostate" << '\n';
    }
  // Prefer Approach above . The don't require any unsafe implice
  // conversions
  /*if (!variant_two.index())
  {
      cout << "Monostate" << '\n';
  }
  if (std::get_if<std::monostate>(&variant_two))
  {
      cout << "Monostate" << '\n';
  }*/
}
template<typename... args> struct make_visitor : args...
{
  explicit make_visitor(args &&...lambdas)
      : args{ lambdas }...
  {
  }
  using args::operator()...;
};
template<typename... args> make_visitor(args...) -> make_visitor<args...>;
auto
visitors() noexcept
{
  // variant<int, string> visitor_var{};
  // visitor_var.emplace<0>(1);
  // std::visit(
  //[](auto &alt_val) {
  // cout << "Alternative value is : " << alt_val << '\n';
  // alt_val += alt_val;
  // cout << "New value is : " << alt_val << '\n';
  //},
  // visitor_var);
  // const auto &&overload = make_visitor(
  //[](int ints) { cout << "ints alt : " << ints << '\n'; },
  //[](string &strings) { cout << "string alt : " << strings << '\n'; });
  // std::visit(overload, visitor_var);
}
