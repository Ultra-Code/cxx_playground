// module;
#include <cstdint>
#include <string>
#include <algorithm>
#include <cmath>
// export module algo.karatsuba;
// import<cstdint>;
// import<string>;
// import<algorithm>;
// import<cmath>;

namespace algo
{

  constexpr auto split_num
      = [](uint64_t number, double at) -> std::pair<uint64_t, uint64_t> {
    constexpr auto base10 = uint8_t(10);
    const auto divisor = std::pow(base10, at);
    auto const &[quotient, reminder]
        = std::div(int64_t(number), int64_t(divisor));
    return { quotient, reminder };
  };

  // export
  auto
  karatsuba(uint64_t left_operand, uint64_t right_operand) -> uint64_t
  {
    auto constexpr single_digit = uint8_t(1);

    auto const left_operand_lenght = std::to_string(left_operand).length();

    auto const right_operand_lenght = std::to_string(right_operand).length();

    if (left_operand_lenght == single_digit
        and right_operand_lenght == single_digit)
      {
        return left_operand * right_operand;
      }

    auto const max_lenght
        = std::ranges::max(left_operand_lenght, right_operand_lenght);

    auto const max_half = std::ceil(max_lenght / 2);

    // split x into x1 and x2 where B is base10 and m max_half x=x1 ∗ B^m +x

    auto const &[left_quotient, left_reminder]
        = split_num(left_operand, max_half);

    const auto &[right_quotient, right_reminder]
        = split_num(right_operand, max_half);

    // the product is xy=(x1∗B^m+x2)(y1∗B^m+y2)
    // which which when expanded is xy=x1∗y1∗B^(2m)+x1∗y2∗B^m+x2∗y1∗B^m+x2∗y2

    auto const quotients = karatsuba(left_quotient, right_quotient);

    auto const reminders = karatsuba(left_reminder, right_reminder);

    auto const left_sum = left_quotient + left_reminder;
    auto const right_sum = right_quotient + right_reminder;
    auto const quotient_reminder_sum
        = karatsuba(left_sum, right_sum) - (quotients + reminders);

    auto const base10_power_2max_half = std::pow(10, 2 * max_half);
    auto const base10_power_max_half = std::pow(10, max_half);

    auto const final_product
        = (double(quotients) * base10_power_2max_half)
          + (double(quotient_reminder_sum) * base10_power_max_half)
          + double(reminders);

    return static_cast<uint64_t>(final_product);
  }
} // namespace algo
