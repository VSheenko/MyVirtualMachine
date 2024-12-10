cmake_minimum_required(VERSION 3.29)
project(MyVirtualMachine)

set(CMAKE_CXX_STANDARD 23)

add_executable(MyVirtualMachine main.cpp
        sources/Machine/Memory/Memory.cpp
        sources/Machine/Memory/Memory.h
        sources/Machine/Processor/Processor.cpp
        sources/Machine/Processor/Processor.h
)
