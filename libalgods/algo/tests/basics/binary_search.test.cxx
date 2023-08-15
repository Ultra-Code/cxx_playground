#include <ut.hpp>
// import boost.ut
#include <src/binary_search.hxx>
#include <vector>
#include <span>
#include <optional>
// import <vector>;
// import <optional>;
// import <span>;
// import algo.binary_search;

using namespace boost::ut;
using namespace boost::ut::bdd;

suite binary_search_test = [] {
  "Binanry Search Test"_test = [] {
    given("Given a sorted array of {1,2,3,4,5,6,7} find 2") = [] {
      auto const array = std::vector{ 1, 2, 3, 4, 5, 6, 7 };
      then("Then 2 is found at the index 1 in the array") = [&array] {
        auto const two = int(2);
        auto const search_result_position
            = algo::binary_search(std::span{ array }, two);
        expect(that % search_result_position.value() == two);
      };
      then("Then if 8 is serched it isn't found") = [&array] {
        auto const eight = int(8);
        auto const search_result
            = algo::binary_search(std::span{ array }, eight);
        expect(that % (search_result == std::nullopt))
            << "search_result != nullopt";
      };
    };
  };
};
