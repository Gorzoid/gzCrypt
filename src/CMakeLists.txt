cmake_minimum_required(VERSION 3.0.0)

add_library(gzCrypt bigint.cpp)
target_include_directories(gzCrypt PUBLIC ../include)
