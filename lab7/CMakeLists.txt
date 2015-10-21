cmake_minimum_required(VERSION 3.3)
project(lab7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")

set(SOURCE_FILES main.c)
add_executable(lab7 ${SOURCE_FILES})