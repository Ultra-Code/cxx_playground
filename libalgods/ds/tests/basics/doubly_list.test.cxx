#include <iterator>
#include <sstream>
#include <ut.hpp>
#include <src/doubly_list.hxx>

using namespace boost::ut;
using namespace boost::ut::bdd;

auto constexpr print = [](auto const &list) {
  std::stringstream stream_list{};
  for (auto const &element : list)
    {
      stream_list << element << ' ';
    }
  return stream_list.str();
};

suite const doubly_list_test = [] {
  "Doubly linked list front_insertion test"_test = [] {
    given("Given an empty doubly list") = [] {
      auto list = ds::doubly_list<int>{};

      then("Then if push_front 1") = [&list] {
        auto constexpr one = uint(1);
        list.push_front(one);
      };

      then("Then if push_front 2") = [&list] {
        auto constexpr two = uint(2);
        list.push_front(two);
        expect(that % list.size() == two) << print(list);
      };
    };
  };

  "Doubly linked list back_insertion test"_test = [] {
    given("Given An empty doubly list {}") = [] {
      auto list = ds::doubly_list<int>{};

      then("Then if push_back 1") = [&list] {
        auto constexpr one = int(1);
        list.push_back(one);
      };

      then("Then if push_back 2") = [&list] {
        auto constexpr two = int(2);
        list.push_back(two);
        expect(that % list.size() == uint(two)) << print(list);
      };
    };
  };

  "Doubly linked list insertion test"_test = [] {
    given("Given a list of {1,3,5}") = [] {
      auto list = ds::doubly_list<int>{ 1, 3, 5 }; // NOLINT

      then("Then list.size == 3") = [&list] {
        auto constexpr three = uint(3);
        expect(that % list.size() == three);
      };

      then("Then if insert(next(begin),two))") = [&list] {
        auto constexpr two = uint8_t(2);
        auto constexpr list_size = uint8_t(4);
        list.insert(std::ranges::next(std::begin(list)), two);
        expect(that % list.size() == list_size) << print(list);
      };

      then("Then if insert(prev(end),four)") = [&list] {
        auto constexpr four = uint8_t(4);
        auto constexpr list_size = uint8_t(5);
        list.insert(std::ranges::prev(std::end(list)), four);
        expect(that % list.size() == list_size) << print(list);
      };

      then("Then if insert(next(begin,two),six)") = [&list] {
        auto constexpr distance = uint8_t(2);
        auto constexpr six = uint8_t(6);
        auto constexpr list_size = uint16_t(6);
        list.insert(std::ranges::next(list.begin(), distance), six);
        expect(that % list.size() == list_size) << print(list);
      };

      then("Then if insert(prev(end,two),seven)") = [&list] {
        auto constexpr distance = uint8_t(2);
        auto constexpr seven = uint8_t(7);
        auto constexpr list_size = uint16_t(7);
        list.insert(std::ranges::prev(list.end(), distance), seven);
        expect(that % list.size() == list_size) << print(list);
      };
    };
  };

  "Doubly linked list find and clear test"_test = [] {
    given("Given the list {1,2,3,4}") = [] {
      auto list = ds::doubly_list{ 1, 2, 3, 4 };

      then("Then if find(four)") = [&list] {
        auto constexpr four = uint16_t(4);
        auto result = list.find(four);
        expect(that % result->value_ == four);
      };

      when("When clear()") = [&list] {
        list.clear();
        then("Then list must be empty")
            = [&list] { expect(that % list.empty()); };
      };
    };
  };

  "Doubly linked list remove operations test"_test = [] {
    given("Given a list of {1,2,3,4,5,6,7}") = [] {
      auto list = ds::doubly_list<int>{ 1, 2, 3, 4, 5, 6, 7 }; // NOLINT

      then("Then if pop_front()") = [&list] {
        list.pop_front();
        auto constexpr list_size = uint16_t(6);
        expect(that % list.size() == list_size) << print(list);
      };

      then("Then if pop_back()") = [&list] {
        list.pop_back();
        auto constexpr list_size = uint16_t(5);
        expect(that % list.size() == list_size) << print(list);
      };

      then("Then if remove(five)") = [&list] {
        auto constexpr five = uint16_t(5);
        list.remove(five);
        auto constexpr list_size = uint16_t(4);
        expect(that % list.size() == list_size) << print(list);
      };
    };
  };

  "Doubly linked list iterator test"_test = [] {
    given("Given the iterator begin of list{1,2,3}") = [] {
      auto list = ds::doubly_list<int>{ 1, 2, 3 };
      auto begining = list.begin();
      auto ending = list.end();

      then("Foward iteration from begin to end") = [&] {
        printer out;
        for (; begining != ending; ++begining)
          {
            out <<*begining << ' ';
          }
        expect(begining == ending) << out.str();
      };

      then("Backwards iteration from end to begin") = [&] {
        printer out;
        --ending;
        for (; begining != ending; --ending)
          {
            out <<*ending << ' ';
          }
        expect(begining == ending) << out.str();
      };
    };
  };
};
