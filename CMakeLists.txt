cmake_minimum_required(VERSION 3.10)
project(compiler_generator_master)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(models)
include_directories(utils)

add_executable(
        main.cpp
        NFABuilder.cpp
        DFABuilder.cpp
        DFABuilder.h
        models/DFAState.cpp
        models/DFAState.h)
