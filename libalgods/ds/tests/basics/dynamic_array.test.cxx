#include <ut.hpp>
#include <src/dynamic_array.hxx>
// import ds.dynamic_array;
// import boost.ut;

using namespace boost::ut;
using namespace boost::ut::bdd;

constexpr auto print = [](auto const &dynamic_array) {
  std::stringstream stream_dynamic_array{};
  for (auto const &element : dynamic_array)
    {
      stream_dynamic_array << element << ' ';
    }
  return stream_dynamic_array.str();
};

suite const dynamic_array_test = [] {
  "dynamic array construtor test"_test = [] {
    given("Give a dynamic array of {5,2}") = [] {
      auto dyna_array = ds::dynamic_array<int>({ 5, 2 });

      when("When the dynamic_array is copied") = [&dyna_array] {
        auto dyna_array_copy = dyna_array;
        then("dyanmic array copy must == {5,2}")
            = [&dyna_array, &dyna_array_copy] {
                expect(that % dyna_array_copy.size() == dyna_array.size())
                    << print(dyna_array);
              };
      };

      when("When dynamic array is moved") = [&dyna_array] {
        auto dyna_size = dyna_array.size();
        auto dyna_array_moved = std::move(dyna_array);
        then("Then dynamic array is in moved from state and the new move "
             "constracted array is that of the previous dynamic array")
            = [&dyna_array, &dyna_array_moved, &dyna_size] {
                expect(that % dyna_array.size() == 0UL);
                expect(that % dyna_array_moved.size() == dyna_size)
                    << print(dyna_array_moved);
              };
      };
    };

    "dyanmic array push_back test"_test = [] {
      when("When new array is constructed with capacity 2") = [] {
        auto array = ds::dynamic_array<int>(2);
        then("Then size is 0 capacity 2") = [&array] {
          expect(that % array.size() == 0UL);
          expect(that % array.capacity() == 2UL);
        };

        when("When push_back(number) is called") = [&array] {
          array.push_back(1);
          then("with push_back(number) size increase and container has number")
              = [&array] {
                  expect(that % array.size() == 1UL) << print(array);
                };
        };

        when("When pop_back() is called") = [&array] {
          array.pop_back();
          then("Then last element removed and size decrease")
              = [&array] { expect(that % array.size() == 0UL); };
        };

        when("When push_back is called more than the capacity") = [&array] {
          array.push_back(1);
          array.push_back(2);
          array.push_back(3);
          then("Then more space must be allocated and elements moved in")
              = [&array] {
                  expect(that % array.size() == 3UL);
                  expect(that % array.capacity() == 4UL) << print(array);
                };
        };
      };
    };

    "dynamic array insertion test"_test = [] {
      given("Given an empty array {} of capacity 5") = [] {
        auto constexpr capacity = 2;
        auto array_list = ds::dynamic_array<int>(capacity);

        when("When insert(begin(),1) ") = [&array_list] {
          auto constexpr two = 2;
          array_list.insert(array_list.begin(), two);
          then("Then array contains 1 and size is 1") = [&array_list] {
            expect(that % array_list.size() == 1UL) << print(array_list);
          };
        };

        when("When 3 more insert are done with values {245}") = [&array_list] {
          auto constexpr one = 1;
          array_list.insert(array_list.begin(), one);
          auto constexpr two_jumps = 2;
          auto constexpr five = 5;
          array_list.insert(std::ranges::next(array_list.begin(), two_jumps),
                            five);
          auto constexpr four = 4;
          array_list.insert(std::ranges::next(array_list.begin(), two_jumps),
                            four);
          then("Then array should contain 4 element and with size 4")
              = [&array_list] {
                  expect(that % array_list.size() == 4UL) << print(array_list);
                };
        };

        when("When inserting 3 after 2 in the range {1,2,4,5}")
            = [&array_list] {
                auto constexpr two_jumps = 2;
                auto constexpr three = 3;
                array_list.insert(
                    std::ranges::next(array_list.begin(), two_jumps), three);
                then("Then range should be {1,2,3,4,5}") = [&array_list] {
                  expect(that % array_list.size() == 5UL
                         and that % array_list.capacity() == 8UL)
                      << print(array_list);
                };
              };

        when("When the array list is filled to its capacity the next insert  "
             "of 7 after 3 should extend it")
            = [&array_list] {
                auto constexpr five_jumps = 5;
                auto constexpr six= 6;
                array_list.insert(
                    std::ranges::next(array_list.begin(), five_jumps), six);
                then("Then array should now be {1,2,3,7,4,5}")
                    = [&array_list] {
                        expect(that % array_list.size() == 6UL)
                            << print(array_list);
                      };
              };
      };
      given("Given an array of {1,2,4,5}") = [] {
        auto array_list = ds::dynamic_array({ 1, 2, 4, 5 });
        when("When insert(next(begin(),3),3)") = [&array_list] {
          array_list.insert(std::ranges::next(array_list.begin(), 2), 3);
          then("Then array must be {1,2,3,4,5}") = [&array_list] {
            expect(that % array_list.size() == 5UL) << print(array_list);
          };
        };
      };
    };
  };
};
