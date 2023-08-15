#include <vector>
#include <numeric>

namespace algo
{
  auto
  merge(std::vector<int> &array, int lower_bound, int middle, int upper_bound)
  {
    auto const left_array_size = middle - lower_bound + 1;
    auto const right_array_size = upper_bound - middle;

    auto left_half = std::vector<int>(left_array_size);
    auto right_half = std::vector<int>(right_array_size);

    // left array copy
    for (int index = 0; index < left_array_size; index++)
      {
        left_half[index] = array[lower_bound + index];
      }
    // right array copy
    for (int index = 0; index < right_array_size; index++)
      {
        right_half[index] = array[middle + index + 1];
      }

    auto left_counter = int();
    auto right_counter = int();
    auto left_lower_bound = lower_bound;

    while (left_counter < left_array_size and right_counter < right_array_size)
      {
        if (left_half[left_counter] <= right_half[right_counter])
          {
            array[left_lower_bound] = left_half[left_counter];
            left_counter++;
          }
        else
          {
            array[left_lower_bound] = right_half[right_counter];
            right_counter++;
          }
        left_lower_bound++;
      }

    while (left_counter < left_array_size)
      {
        array[left_lower_bound] = left_half[left_counter];
        left_counter++;
        left_lower_bound++;
      }

    while (right_counter < right_array_size)
      {
        array[left_lower_bound] = right_half[right_counter];
        right_counter++;
        left_lower_bound++;
      }
  }

  auto
  merge_sort(std::vector<int> &array, int lower_bound, int upper_bound) -> void
  {
    auto const middle = std::midpoint(lower_bound, upper_bound);
    if (lower_bound < upper_bound)
      {
        merge_sort(array, lower_bound, middle);
        merge_sort(array, middle + 1, upper_bound);
        merge(array, lower_bound, middle, upper_bound);
      }
  }
} // namespace algo
