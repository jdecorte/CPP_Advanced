cmake_minimum_required(VERSION 3.5.0)
project(readings VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

set(INCLUDE_DIR ./libs)

include_directories(${INCLUDE_DIR})

add_executable(readings readings.cpp)


