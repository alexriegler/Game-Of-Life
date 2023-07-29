# Game Of Life

This project is still a work-in-progress.

For background information regarding the Game of Life, see the [Conway's Game of Life Wikipedia page](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).

## About

The purpose of this project is to demonstrate C++20's enhanced template metaprogramming support, specifically this project makes extensive usage of [NTTPs](https://en.cppreference.com/w/cpp/language/template_parameters) (non-type template parameters) of the [literal class type](https://en.cppreference.com/w/cpp/named_req/LiteralType). The way I approached programming in this project was almost purely functional and, as a result, the syntax is reminiscent of [Haskell](https://www.haskell.org/). In fact, this implementation is very similar to a Haskell implementation I did in the past.

In the process of creating this demo, I had to make a conscious effort to avoid using `constexpr` functions, as everything could have easily been done in that fashion instead.

## Testing
A secondary purpose of this project was for me to practice my TDD (test driven development) skills.

The tests can be found in [GameOfLife.cpp](./src/GameOfLife.cpp).

## Requirements

* CMake 3.20+
* MSVC 19.33.31517+
* vcpkg 2022-05-05-67e17c1782801cf481be9ac0b3765dff3e4bdeb8+
  * Catch2 3.0.1#1+ installed

## Build

This project was tested on Windows 11 with [Visual Studio 2022 17.3.0 Preview 2.0](https://visualstudio.microsoft.com/vs/preview/). The code should compile with any C++20 standard-compliant compiler.

You can build the project with CMake by using the following commands from the root directory:

```bash
cmake -S . -B build -D CMAKE_TOOLCHAIN_FILE=$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

At the moment, the project only produces a test executable. The test executable is named "GameOfLife" and it simply runs the Catch2 test cases.
