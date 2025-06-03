cmake_minimum_required(VERSION 3.30)
project(IBCF_with_Cosine_Simularity)

set(CMAKE_CXX_STANDARD 20)

add_executable(IBCF_with_Cosine_Simularity src/main.cpp
        src/ibcf.cpp
        src/ibcf.h
        src/utils.h
        src/utils.cpp)
