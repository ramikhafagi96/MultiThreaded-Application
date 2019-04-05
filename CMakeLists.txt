cmake_minimum_required(VERSION 3.12)
project(MultiThreading_Lab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(MultiThreading_Lab2 main.cpp ./MatrixMultiplication/MatrixMultiplication_Prog.cpp ./MatrixMultiplication/MatrixMultiplication_Int.h MergeSort/MergeSort_Prog.cpp MergeSort/MergeSort_Int.h ImportantIncludes.h)