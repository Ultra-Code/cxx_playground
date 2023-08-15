cmake_minimum_required(VERSION 3.18)
project(qtcallback VERSION 0.0.1 DESCRIPTION "Qt5 callbacks" LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH "${Qt5_DIR}")
add_executable(qtcallback src/main.cpp)
set_target_properties(qtcallback PROPERTIES CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
target_compile_options(qtcallback PRIVATE -Werror -Wall -Wextra -pedantic
    -pedantic-errors -stdlib=libc++ -std=c++20)
find_package(Qt5 5.15 COMPONENTS Core REQUIRED)
target_link_libraries(qtcallback Qt5::Core)
