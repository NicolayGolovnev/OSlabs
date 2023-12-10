cmake_minimum_required(VERSION 3.24)
project(OSlabs)

set(CMAKE_CXX_STANDARD 14)
# Для 3 лабы
# link_libraries(ws2_32 wsock32)

add_executable(OSlabs main.cpp lab1/PackageExec.cpp lab3/server/ServerRun.cpp lab3/client/ClientRun.cpp
        lab2/PackageExec.cpp)
add_executable(lab1
        lab1/Terminal.h
        lab1/PackageTaskUtil.h
        lab1/PackageTask.h
        lab1/Package.h
        lab1/PackageExec.cpp
)

add_executable(lab2
        lab2/Terminal.h
        lab2/PackageTaskType.h
        lab2/PackageTask.h
        lab2/Package.h
        lab2/PackageExec.cpp
        lab2/TaskExecution.h
        lab2/template/DictTemplate.h
)

add_executable(lab3_server
        lab3/server/Server.h
        lab3/util/TCP.h
        lab3/util/User.h
        lab3/util/ClientServerHelper.h
        lab3/server/ServerRun.cpp
)
add_executable(lab3_client
        lab3/client/Client.h
        lab3/util/TCP.h
        lab3/util/User.h
        lab3/util/ClientServerHelper.h
        lab3/client/ClientRun.cpp
)