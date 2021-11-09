cmake_minimum_required(VERSION 3.20)
project(astULL)

set(CMAKE_CXX_STANDARD 14)

add_executable(astULL src/main.cpp src/MetaParameter.cpp src/MetaParameter.h src/Board.cpp src/Board.h src/EvoAlgo.cpp src/EvoAlgo.h)
