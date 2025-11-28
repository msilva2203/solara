cmake_minimum_required(VERSION 3.20)

# solara
project(solara VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(
    solara
    source/main.cpp
    source/solara/solara.h
    source/solara/solara.cpp
    source/solara/token.h
    source/solara/token.cpp
    source/solara/lexer.h
    source/solara/lexer.cpp
    source/solara/stringtable.h
    source/solara/stringtable.cpp
    source/solara/ast.h
    source/solara/ast.cpp
    source/solara/parser.h
    source/solara/parser.cpp
)

target_compile_features(solara PUBLIC cxx_std_20)

# Compiler warnings
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(solara PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(solara PRIVATE /W4)
endif()
