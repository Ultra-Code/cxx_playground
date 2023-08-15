/** @file structured_binding.cxx */

/**
 *@brief Structured Binding
 *
 *Detailed description
 */
#include <experimental/array>
//#include <iostream>
#include <span>
//#include <string>
//#include <unordered_map>
// import "experimental/array";
import<iostream>;
// import<span>;
import<string>;
import<unordered_map>;

/**
 * @fn auto whatsHappenningInTheStructure(int v)-> void.
 * @brief show whats happening in a struct @a v.
 *
 * @param v Receives the variable v.
 */
auto whatsHappenningInTheStructure(int v) -> void;
//! @struct binding
//! @brief A struct with 2 data types
/*
 *Some details about struct
 */
struct binding {
  uint64_t integer{}; //!< A 64bit unisigned int.
  std::string string{};    //!< A std::string.
};

auto
arrayreturn() -> auto {
  auto const a = std::experimental::make_array(1, 2, 3);
  return a;
}

auto
maps() -> decltype(auto) {
  return std::unordered_map<uint32_t, std::string>(
      {{1, "one"}, {2, "two"}});
}

auto
use_structures(int argc, char *argv[]) -> int {
  const auto &[a, b, c] = arrayreturn();
  using std::cout, std::endl, std::cerr;
  constexpr auto alignment_offset{std::uint8_t{16}};
  alignas(alignment_offset) const auto &&[i, s] =
      binding{.integer = 1, .string = {"This is awesome now"}};
  for (const auto &[number, words] : maps()) {
    cout << " number is " << number << " and word is " << words << '\n';
  }
  if (argc < 2) {
    cerr << "error: missing name" << endl;
    return 1;
  }
  auto span{std::span(argv, 2)};
  cout << "Hello, " << span.back() << '!' << endl;
  cout << i << " and " << s << " \n";
  whatsHappenningInTheStructure(3);
}
template<std::size_t>
auto get(const int &c) -> auto;
/**
 * @brief how structures behave.
 *This depends on the type of it anonimous objs.
 *
 *If the structure is binded using a const & the anonimous obj
 *is refered to using a ref so a modification to the original
 *object affects the entries of the anonimous obj but if the
 *structure binds by value it has it independent copy so a modification
 *of either the original or anonimous obj doesn't affects one another
 */
auto
whatsHappenningInTheStructure(int v /*!< [in,out]  @param v no input.*/)
    -> void {
  auto structure /*!< structures */ {
      binding{.integer = 1, .string = {"Nothing"}}};
  /** @var ints int in struct
   * @var str string in struct.
   */
  const auto &[ints, str] = structure;
  /// structural bindings get the exact type as their initializers and don't
  /// decay but after the initialization it entries can decay ie.lose of info
  /// dependening on conversions

  /**
   * What happens is the @var structure is converted to an r-value which
   * can be moved if a move constructor and or move assign operator are
   * available which isn't neccessaryly true for our anonimous obj which is
   * destructured into @var i and @var s
   * but lets not for get a r-value reference is just another type of l-value
   * reference so even though @a structure isn't moved the structured entries
   * in the anonimous obj reference those in structure so if they are move
   * then those entries in @a structure are moved and empty
   */
  auto &&[i, s] = std::move(structure);
  std::cout << "Suprise object not moved after std::move(structure)"
            << structure.integer << " \n";
  const auto var = std::move(s);
  const auto ins = std::move(i);
  std::cout << "Var contains " << var << " which is the value of" << s
            << " oopus now moved" << structure.string
            << " .string Now big ooopus\n";
  std::cout << ints << " number and " << str << " \n";
  structure.integer = 33;
  std::cout << "modified number " << ints << " number and " << str << " \n";
  std::cout << "moved number " << ins << " number and " << var << " \n";
}
