cmake_minimum_required(VERSION 3.18)
project(
  oatpp-exe
  VERSION 0.0.1
  DESCRIPTION "Qt5 callbacks"
  LANGUAGES CXX)
find_package(oatpp 1.1.0 REQUIRED)
add_executable(oatpp-exe src/main.cpp)
set_target_properties(
  oatpp-exe
  PROPERTIES CXX_STANDARD 20
             CXX_STANDARD_REQUIRED ON
             CXX_EXTENSIONS OFF)
target_compile_options(
  oatpp-exe PRIVATE -Wall -Wextra -pedantic -pedantic-errors -Wl,-z,notext
)# -stdlib=libstdc++
# find_package(Qt5 5.15 COMPONENTS Core Widgets REQUIRED)
target_link_libraries(oatpp-exe PRIVATE oatpp::oatpp)
