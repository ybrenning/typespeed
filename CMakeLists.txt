cmake_minimum_required(VERSION 3.20)
project(typespeed)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(typespeed typespeed.c typespeed.h sentences.h)
target_link_libraries(typespeed ${CURSES_LIBRARIES})
