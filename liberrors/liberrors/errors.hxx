/**
 * @file errors.hxx
 */
#pragma once
#include <source_location>
#include <string_view>
#include <stdexcept>

#include <liberrors/export.hxx>

/**
 * @namespace errors
 * @brief namespace containing functions for error handling
 */
namespace errors
{
  /**
   * @brief function to assert that @param condition is true else failfast with
   * the error message @param assert_msg
   *
   * @param [in] condition to check
   * @param [in] assert_msg :message to print to stderr when @param condition
   * is false
   * @returns void
   */

  auto
  assert_that(bool condition, std::string_view assert_msg,
              std::source_location loc
              = std::source_location::current()) noexcept -> void;

  auto
  trace_on_abort() -> void;

  class recoverable_err : std::exception
  {
    std::string message;

  public:
    explicit recoverable_err(std::string_view msg,
                             std::source_location loc
                             = std::source_location::current()) noexcept;
    [[nodiscard]] auto
    what() const noexcept -> const char * override;
  };
} // namespace errors
