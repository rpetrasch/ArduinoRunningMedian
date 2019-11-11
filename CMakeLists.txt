cmake_minimum_required(VERSION 3.15)
project(RunningMedian)

set(CMAKE_CXX_STANDARD 17)

add_executable(RunningMedian src/main.cpp src/HeapUtils.h src/HeapUtils.cpp src/Heap.cpp src/Heap.h src/RunningMedian.cpp src/RunningMedian.h)