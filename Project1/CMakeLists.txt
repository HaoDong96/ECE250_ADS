cmake_minimum_required(VERSION 3.13)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project1
        Double_node_tester.h
        Double_sentinel_list.h
        Double_sentinel_list_driver.cpp
        Double_sentinel_list_tester.h
        ece250.h
        Exception.h
        test.cpp
        Tester.h)
