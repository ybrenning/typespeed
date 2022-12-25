cmake_minimum_required(VERSION 3.20)
project(typespeed)

set(CMAKE_C_STANDARD 11)

add_executable(typespeed typespeed.c typespeed.h sentences.h)
