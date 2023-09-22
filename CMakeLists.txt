cmake_minimum_required(VERSION 3.24)
project(OSlabs)

set(CMAKE_CXX_STANDARD 17)

add_executable(OSlabs main.cpp lab1/Terminal.h lab1/PackageTaskEnum.h lab1/PackageTask.cpp lab1/PackageTask.h lab1/Package.h lab1/Package.cpp)
