cmake_minimum_required(VERSION 3.20)
project(typespeed)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(typespeed typespeed.c sentences.h)
