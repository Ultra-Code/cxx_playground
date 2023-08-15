#include <ut.hpp>
#include <src/karatsuba.hxx>
// import algo.karatsuba;
// import boost.ut;

using namespace boost::ut;
using namespace boost::ut::bdd;

suite karatsuba_test = [] {
  "Karatsuba Test"_test = [] {
    given("Given the task of multiplying 111111 and 101010") = [] {
      then("Then karatsuba of operands == 111111*101010") = [] {
        auto constexpr left_operand = uint64_t(111111);
        auto constexpr right_operand = uint64_t(101010);
        expect(that % algo::karatsuba(left_operand, right_operand)
               == left_operand * right_operand);
        expect(that % algo::karatsuba(1, 2) == 1UL * 2UL);
      };
    };
  };
};
