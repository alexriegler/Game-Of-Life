find_package(Catch2 3 REQUIRED)

add_executable (GameOfLife "GameOfLife.cpp" "GameOfLife.h" "Coordinates.h" "GameState.h" "Adjacents.h" "Generation.h")

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(GameOfLife PUBLIC
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wconversion;-Wshadow;-Wpedantic;-Wformat=2;-Wunused>>"
    "$<${msvc_cxx}:$<BUILD_INTERFACE:-W4;-WX>>"
)

target_link_libraries(GameOfLife PRIVATE Catch2::Catch2WithMain)

# target_compile_features(GameOfLife PUBLIC cxx_std_20)
set_property(TARGET GameOfLife PROPERTY CXX_STANDARD 20)
set_property(TARGET GameOfLife PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET GameOfLife PROPERTY CXX_EXTENSIONS OFF)

# TODO: Add tests and install targets if needed.
