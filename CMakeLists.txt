cmake_minimum_required(VERSION 3.20)

# solara
project(solara VERSION 1.0)
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
)