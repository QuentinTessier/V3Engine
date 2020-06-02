cmake_minimum_required(VERSION 3.10)
project(V3Engine VERSION 0.1.1 LANGUAGES C)

add_executable(V3Engine
    src/main.c
    src/window/window_linux.c
)

target_link_libraries(V3Engine PRIVATE -lxcb)