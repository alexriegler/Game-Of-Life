# CMakeList.txt : CMake project for GameOfLife, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

project ("GameOfLife")

find_package(Catch2 3 REQUIRED)

add_executable (GameOfLife "GameOfLife.cpp" "GameOfLife.h")

target_link_libraries(GameOfLife PRIVATE Catch2::Catch2WithMain)

set_property(TARGET GameOfLife PROPERTY CXX_STANDARD 20)

# TODO: Add tests and install targets if needed.
