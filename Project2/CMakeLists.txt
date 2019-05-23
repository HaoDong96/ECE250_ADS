cmake_minimum_required(VERSION 3.13)
project(Project2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project2
        ece250.h
        Exception.h
        Resizable_deque.h
        Resizable_deque_driver.cpp
        Resizable_deque_tester.h
        Tester.h)
