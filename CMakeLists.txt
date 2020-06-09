cmake_minimum_required(VERSION 3.10)
project(V3Engine VERSION 0.1.1 LANGUAGES C)

IF (WIN32)
    add_executable(V3Engine
        src/main.c
        src/window/V3Win32/V3Win32.c
        src/window/V3Window.c
    )
ELSE()
    add_executable(V3Engine
        src/main.c
        src/window/V3xcb/V3xcb.c
        src/window/V3Window.c
    )

    target_link_libraries(V3Engine PRIVATE -lxcb)
    target_link_libraries(V3Engine PRIVATE -lxkbcommon)
ENDIF()


