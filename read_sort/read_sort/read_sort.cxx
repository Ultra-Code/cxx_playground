#include <cerrno>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <iterator>
#include <locale>
#include <ranges>
#include <string>
#include <span>
#include <system_error>
#include <vector>
#include <iostream>
#include <algorithm>

template<typename char_type> struct text : std::basic_string<char_type>
{
  explicit constexpr operator bool() const noexcept
  {
    return not this->empty();
  }
};

auto
print(std::ostream &out, std::vector<text<char>> const &array) -> void
{
  out.imbue(std::locale(""));
  std::ranges::copy(array, std::ostream_iterator<text<char>>(std::cout, " "));
  /*
   *for (auto const &element : array)
   *  {
   *    out << element << "   ";
   *  }
   */
  out << '\n';
}

auto
sort_input(std::vector<text<char>> &input) -> std::vector<text<char>>
{
  auto local_locale = std::locale("");
  std::ranges::sort(input, local_locale);
  return input;
}

auto
read_input(int argc, char *argv[]) -> int
{

  auto constexpr read
      = []<typename char_type>(std::basic_istream<char_type> &instream)
      -> std::vector<text<char_type>> {
    auto text_array = std::vector<text<char_type>>();
    auto texts = text<char_type>();

    /*
     *while (std::getline(instream, texts))
     *  {
     *    text_array.emplace_back(std::move(texts));
     *  }
     */
    // std::ranges::move(std::ranges::istream_view<text<char>>(instream),
    // std::back_inserter(text_array));
    text_array.insert(std::begin(text_array),
                      std::istream_iterator<text<char>>(instream), {});
    // std::move(std::istream_iterator<text<char>>(instream), {},
    // std::back_inserter(text_array));
    return text_array;
  };

  std::cin.exceptions(std::ios::badbit);

  auto constexpr command_line_args
      = [](int arg_count) { return arg_count == 1; };

  if (command_line_args(argc))
    {
      auto standard_input_text_array = read(std::cin);

      print(std::cout, sort_input(standard_input_text_array));
    }
  else
    {
      auto infile_stream = std::ifstream(argv[1]); // NOLINT
      if (not infile_stream.is_open())
        {
          // NOLINTNEXTLINE
          std::cerr << argv[1] << " : "
                    << std::system_category().message(errno);
          return EXIT_FAILURE;
        }
      auto file_input_text_array = read(infile_stream);
      print(std::cout, sort_input(file_input_text_array));
    }
  return 0;
}

auto
main(int argc, char *argv[]) -> int
{
  read_input(argc, argv);
}
