cmake_minimum_required(VERSION 3.20)
project(typespeed)

set(CMAKE_C_STANDARD 11)

if (UNIX)
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
endif (UNIX)

add_executable(typespeed typespeed.c typespeed.h sentences.h)

if (UNIX)
    target_link_libraries(typespeed ${CURSES_LIBRARIES})
endif (UNIX)
