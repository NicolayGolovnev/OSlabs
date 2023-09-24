cmake_minimum_required(VERSION 3.24)
project(OSlabs)

set(CMAKE_CXX_STANDARD 14)

add_executable(OSlabs lab1/Terminal.h lab1/PackageTaskUtil.h lab1/PackageTask.h lab1/Package.h main.cpp lab1/PackageExec.cpp)
