#pragma once
#include <vector>

namespace algo
{
  auto
  selection_sort(std::vector<int> const &array) -> std::vector<int>
  {
    for (auto counter = size_t(), current_min = size_t();
         counter < array.size() - 1; ++counter)
      {
        current_min = counter;
        for (auto swap_counter = counter + 1; swap_counter < array.size();
             ++swap_counter)
          {
            if (array.at(swap_counter) < array.at(current_min))
              {
                current_min = swap_counter;
              }
          }
        std::swap(array.at(current_min), array.at(counter));
      }
  }
} // namespace algo
