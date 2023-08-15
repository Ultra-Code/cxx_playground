#pragma once
#include <vector>

inline auto
insertion_sort(std::vector<int> &array)
{
  for (size_t i = 1; i < array.size() - 1; i++)
    {
      auto key = array[i];

      auto inner_counter = i;
      while (inner_counter > 0 and array[inner_counter - 1] > key)
        {
          array[inner_counter] = array[inner_counter - 1];
          inner_counter--;
        }
      array[inner_counter] = key;
    }
}
