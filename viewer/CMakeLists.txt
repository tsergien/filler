cmake_minimum_required(VERSION 3.20)
project(filler_viewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # for clangd / editor autocompletion

add_compile_options(-Wall -Wextra -Werror)

find_package(SDL3 REQUIRED CONFIG)
find_package(Threads REQUIRED)

# Everything that doesn't need SDL: parsing + the reader thread.
add_library(viewer_core STATIC src/Parser.cpp src/Reader.cpp)
target_include_directories(viewer_core PUBLIC src)
target_link_libraries(viewer_core PUBLIC Threads::Threads)

# The SDL app.
add_executable(filler_viewer src/main.cpp src/Renderer.cpp)
target_link_libraries(filler_viewer PRIVATE viewer_core SDL3::SDL3)

# Tests: ctest --test-dir build
enable_testing()
add_executable(parser_test tests/parser_test.cpp)
target_link_libraries(parser_test PRIVATE viewer_core)
add_test(NAME parser
         COMMAND parser_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample.log)
