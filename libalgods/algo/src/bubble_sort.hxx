#include <vector>

namespace algo
{
  [[nodiscard]] auto
  bubble_sort(std::vector<int> &array) noexcept -> std::vector<int>
  {
    auto const size = array.size() - 1;
    for (size_t counter = 0; counter < size; counter++)
      {
        for (size_t index = 0; index < size - counter; index++)
          {
            if (array[index] > array[index + 1])
              {
                std::swap(array[index], array[index + 1]);
              }
          }
      }
    return array;
  }
} // namespace algo
