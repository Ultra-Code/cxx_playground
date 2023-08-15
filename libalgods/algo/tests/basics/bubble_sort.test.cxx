#include <ut.hpp>
#include <src/bubble_sort.hxx>
#include <iostream>

using namespace boost::ut;
using namespace boost::ut::bdd;

suite const bubble_sort_test = [] {
  "Bubble sort test"_test = [] {
    given("Given an array of 93714082") = [] {
      auto array = std::vector{ 9, 3, 7, 1, 4, 0, 8, 2 };
      when("When bubble sorted") = [&array] {
        auto bubble_sorted_array = algo::bubble_sort(array);
        then("Then 93714082 must now be 01234789")
            = [&array, &bubble_sorted_array] {
                expect(that % array == bubble_sorted_array);
              };
      };
      [&array]{
      for (auto const value : array)
        {
          std::cout << value << " , ";
        }}();
    };
  };
};
