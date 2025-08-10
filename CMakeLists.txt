cmake_minimum_required(VERSION 3.31)

project(GameOfLife)

set(CMAKE_C_STANDARD 23)

include_directories(include/)


# Build raylib as a DLL
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(deps/raylib )

add_executable(gol src/gol.c src/board.c src/screen.c)

target_link_libraries(gol PRIVATE raylib)

add_custom_command(TARGET gol POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/build/raylib/raylib.dll ${CMAKE_CURRENT_BINARY_DIR}
)