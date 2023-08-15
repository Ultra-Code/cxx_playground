cmake_minimum_required(VERSION 3.18)
project(wx-try LANGUAGES CXX)
find_package(wxWidgets 3.1 REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
add_executable(wx-try src/main.cpp)
set_target_properties(
  wx-try
  PROPERTIES CXX_STANDARD 20
             CXX_STANDARD_REQUIRED ON
             CXX_EXTENSIONS OFF)
target_compile_options(wx-try PRIVATE -Wall -Wextra -pedantic -pedantic-errors
                                      -stdlib=libstdc++)
target_link_libraries(wx-try ${wxWidgets_LIBRARIES})
