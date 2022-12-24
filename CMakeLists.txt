cmake_minimum_required(VERSION 3.23)
project(AdvProg1_4)

set(CMAKE_CXX_STANDARD 11)

add_executable(AdvProg1_4 MainDistance.cpp
        Algorithms.h
        Algorithms.cpp
        TypeVector.h
        TypeVector.cpp
        knnServer.cpp knnServer.h MainDistance.h)
