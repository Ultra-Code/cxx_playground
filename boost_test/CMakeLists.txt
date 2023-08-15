cmake_minimum_required(VERSION 3.18)
project(
  boost-test
  VERSION 0.0.1
  DESCRIPTION "Qt5 callbacks"
  LANGUAGES CXX)
add_executable(boost-test src/main.cpp)
set_target_properties(
  boost-test
  PROPERTIES CXX_STANDARD 20
             CXX_STANDARD_REQUIRED ON
             CXX_EXTENSIONS OFF)
target_compile_options(boost-test PRIVATE -Werror -Wall -Wextra -pedantic
                                          -pedantic-errors)
find_package(
  Boost 1.74.0
  COMPONENTS unit_test_framework
  REQUIRED)
target_link_libraries(boost-test Boost::unit_test_framework)
