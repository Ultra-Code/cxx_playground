#include <cerrno>
#include <iterator>
#include <ranges>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <system_error>
#include <unordered_map>

auto constexpr map_range_insert = [] {
  auto map = std::unordered_map<int, int>();
  std::ranges::move(
      std::ranges::istream_view<int>(std::cin)
          | std::ranges::views::transform([](auto const &node_value) {
              return std::make_pair(node_value, 1);
            }),
      std::inserter(map, map.begin()));
  return map;
};

auto
copy_file_content()
{
  namespace fs = std::filesystem;
  auto const input_path = fs::path("./compile_commands.json");
  auto compile_json_file = std::ifstream(input_path);
  if (not compile_json_file.is_open())
    {
      std::cerr << input_path.string() << " : "
                << std::system_category().message(errno) << '\n';
      return EXIT_FAILURE;
    }

  auto const output_path = fs::path("./compilation_db.json");
  auto compile_json_output = std::ofstream(output_path, std::ios_base::trunc);
  if (not compile_json_output.good())
    {
      std::cerr << output_path.string() << " : "
                << std::system_category().message(errno) << '\n';
      return EXIT_FAILURE;
    }
  std::cout << "Written content of " << input_path.string() << " to "
            << output_path.string() << '\n';
  std::ranges::move(std::ranges::istream_view<char>(compile_json_file),
                    std::ostream_iterator<char>(compile_json_output));
}
auto
main(int argc, char **argv) -> int
{
  for (auto const &map = map_range_insert(); auto const &[key, value] : map)
    {
      std::cout << "key : " << key << " value : " << value << '\n';
    }
}
