cmake_minimum_required(VERSION 3.18)
project(qt5network VERSION 0.0.1 DESCRIPTION "An async code using qt5"
    LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH "${Qt5_DIR}")
add_executable(qt5network src/main.cpp)
set_target_properties(qt5network PROPERTIES CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
find_package(Qt5 5.15 REQUIRED COMPONENTS Core Network)
target_link_libraries(qt5network Qt5::Core Qt5::Network)

