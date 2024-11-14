cmake_minimum_required(VERSION 3.5.0)
project(multithreading VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR C:/Users/jcor864/git/libs)

include_directories(${INCLUDE_DIR})

add_executable(multithreading CooperativeCancelation.cpp)

# Link against the threading library
# target_link_libraries(multithreading PRIVATE pthread)


