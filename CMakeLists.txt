cmake_minimum_required(VERSION 3.31)

project(GameOfLife)

set(CMAKE_C_STANDARD 23)

include_directories(include/)


add_subdirectory(deps/raylib build/)

add_executable(gol src/gol.c)

