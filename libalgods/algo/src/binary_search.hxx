//#include <src/algo/export.hxx>
// module;
#include <cmath>
#include <numeric>
#include <cstdint>
#include <optional>
#include <span>
// export module algo.binary_search;
// import<cmath>;
// import<numeric>;
// import<cstdint>;
// import<span>;

// export
namespace algo
{
  template<typename return_type>
  auto
  binary_search(std::span<const auto> const &range, return_type const &element)
      -> std::optional<return_type>
  {
    auto left = uint32_t(0);
    auto right = uint32_t(range.size() - 1);

    while (left <= right)
      {
        auto middle_position = std::midpoint(left, right);
        auto const middle_value = range[middle_position];

        if (element > middle_value)
          {
            left = middle_position + 1;
          }
        else if (element < middle_value)
          {
            right = middle_position - 1;
          }
        else //(element == middle_value)
          {
            return range[middle_position];
          }
      }
    return std::nullopt;
  }
} // namespace algo
