//#include <array>
//#include <cstdint>
//#include <iostream>      //std::cout && std::endl
//#include <memory>        //std::make_unique<>
//#include <string>        //std::string
//#include <unordered_map> //std::unordered_map<>
//#include <vector>        //std::vector
import<array>;
import<cstdint>;
import<iostream>;
import<memory>;
import<string>;
import<unordered_map>;
import<vector>;
import<utility>;

/**
 *Know Limitation :
 *  1: Not Enoght Unit Testing There Might Be Subtle Bugs(Only tested 1 - a
 *million)
 *  2: Bad Choices For some variable names and Functions making some
 *them difficult to follow and understand
 *  -- --But I will be available for any clarification and explanations
 */

namespace Convert {
  // Bring these objects into the Convert namespacse scope
  using std::vector, std::unordered_map, std::cout, std::string, std::to_string,
      std::stoul;
  class NumberToWordConvertor {
  private:
    uint64_t m_number{};
    const uint64_t m_number_copy{};
    const uint64_t m_21{21};
    vector<string> m_words{};
    string m_place_value{};
    const string m_zero{"0"};
    string m_stringified_number{};
    size_t m_number_of_digits{};
    uint64_t m_unit{};
    uint64_t m_unit_lenght{};
    const unordered_map<uint64_t, string> m_dictionary{
        {1, "One"},
        {2, "Two"},
        {3, "Three"},
        {4, "Four"},
        {5, "Five"},
        {6, "Six"},
        {7, "Seven"},
        {8, "Eight"},
        {9, "Nine"},
        {10, "Ten"},
        {11, "Eleven"},
        {12, "Twelve"},
        {13, "Thirtheen"},
        {14, "Fourtheen"},
        {15, "Fitheen"},
        {16, "Sixteen"},
        {17, "Seventeen"},
        {18, "Eighteen"},
        {19, "Nineteen"},
        {20, "Twenty"},
        {30, "Thirty"},
        {40, "Forty"},
        {50, "Fifty"},
        {60, "Sixty"},
        {70, "Seventy"},
        {80, "Eighty"},
        {90, "Ninety"},
        {100, "Hundred"},
        {1000, "Thousand"},
        {1000'000, "Million"},
        {1'000'000'000, "Billion"}};

  public:
    explicit NumberToWordConvertor(uint64_t number)
        : m_number{number}
        , m_number_copy{number}
        , m_stringified_number{to_string(m_number)}
        , m_number_of_digits{m_stringified_number.length()} {}

    // Insert Found Words in the Dictionary into the word vector
    auto
    insertWords(const uint64_t number_to_words) {
      if (m_dictionary.find(number_to_words) != m_dictionary.cend()) {
        m_words.push_back(m_dictionary.find(number_to_words)->second);
      }
    }

    // convert Once and tense to words
    auto
    onceAndTense() {
      if (m_number_of_digits == 1 || m_number < m_21) {
        insertWords(m_number);
      } else {
        for (const auto &digits : m_stringified_number) {
          if (m_number_of_digits == 2) {
            m_place_value = digits;
            for (auto zero_counter{m_number_of_digits}; zero_counter > 0;
                 --zero_counter) {
              if (m_place_value == "0") {
                zero_counter = 1;
                --m_number_of_digits;
              } else if (zero_counter == 1) {
                auto tense_value = stoul(m_place_value);
                auto once_value  = m_number - tense_value;
                insertWords(tense_value);
                if (once_value > 0) {
                  insertWords(once_value);
                }
                m_number_of_digits -= 2;
              } else {
                m_place_value += m_zero;
              }
            }
          }
        }
      }
    }

    // Update the state of the variables after relivant changes in
    // function
    auto
    updateNumber(const uint64_t unit, const uint64_t value) {
      m_stringified_number =
          to_string(stoul(m_stringified_number) - (unit * value));
      m_number           = stoul(m_stringified_number);
      m_number_of_digits = m_stringified_number.length();
    }

    // A special update function for OnceAndTense When Forming the
    // Hundreds Of Thousands
    auto
    updateForOnceAndTenseWhenInThousands(const uint64_t unit,
                                         const uint64_t value) {
      m_stringified_number = to_string(m_unit - (unit * value));
      m_number             = stoul(m_stringified_number);
      m_number_of_digits   = m_stringified_number.length();
    }

    // Convert Hundreds To Words
    auto
    hundreds() {
      const auto hundred_place = 100;
      // insertor for the Hundreds in the thousands 100,000
      if (m_number_of_digits != 3 && m_unit_lenght == 3) {
        auto unit = m_unit / hundred_place;
        insertWords(unit);
        insertWords(hundred_place);
        updateForOnceAndTenseWhenInThousands(unit, hundred_place);
        m_words.emplace_back("And");
        onceAndTense();
      }
      // Regular Hundred Insertor
      if (m_number_of_digits == 3) {
        m_unit = m_number / hundred_place;
        insertWords(m_unit);
        insertWords(hundred_place);
        m_words.emplace_back("And");
        updateNumber(m_unit, hundred_place);
      }
      onceAndTense();
    }

    // Convert Thousands To Words
    auto
    thousands() {
      const auto thousand_place{1'000};
      m_unit        = m_number / thousand_place;
      m_unit_lenght = to_string(m_unit).length();
      auto local_stringified{m_stringified_number};
      auto local_unit{m_unit};
      if (m_unit_lenght == 3) {
        // Update Number To Current State Father Hundreds
        // Manipulations in the Thousands coloumn
        hundreds();
        // restoring state of stringified to help resume to Where We
        // Let Off Before the actual Hundreds
        m_stringified_number = local_stringified;
        updateNumber(local_unit, thousand_place);
      } else if (m_unit_lenght == 2) {
        onceAndTense();
      } else {
        insertWords(m_unit);
        updateNumber(local_unit, thousand_place);
      }
      insertWords(thousand_place);
      hundreds();
    }

    // Convert Million to words
    auto
    million() {
      const auto million_place{1'000'000};
      m_unit = m_number / million_place;
      insertWords(m_unit);
      insertWords(million_place);
      updateNumber(m_unit, million_place);
      thousands();
    }

    // Main conversion Function Where all the Apporiate conversion
    // functions are called
    auto
    converNumberToWords() {
      constexpr auto three{3};
      constexpr auto six{6};
      constexpr auto seven{7};
      cout << "Converting  " << m_number_copy << "  To Words .....            "
           << '\n';
      if (m_number_of_digits < three) {
        onceAndTense();
      } else if (m_number_of_digits == three) {
        hundreds();
      } else if (m_number_of_digits > three && m_number_of_digits < seven) {
        thousands();
      } else if (m_number_of_digits > six) {
        million();
      }
    }

    // Print Converted Words
    auto
    printWords() const {
      cout << "The number " << m_number_copy << " in words is :\n";
      for (const auto &view : m_words) {
        cout << view << " ";
      }
    }

  }; // class NumberToWordConvertor
} // namespace Convert
