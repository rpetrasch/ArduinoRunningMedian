cmake_minimum_required(VERSION 3.15)
project(RunningMedian)

set(CMAKE_CXX_STANDARD 17)

add_executable(RunningMedian src/main.cpp
        src/HeapUtils.h src/HeapUtils.cpp
        src/Heap.h src/Heap.cpp
        src/RunningMedian.h src/RunningMedian.cpp
        src/StringUtils.h src/StringUtils.cpp )