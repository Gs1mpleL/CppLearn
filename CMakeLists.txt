cmake_minimum_required(VERSION 3.25)
project(CppLearn)

set(CMAKE_CXX_STANDARD 14)

add_executable(CppLearn
        base/hello.cpp
        base/常量.cpp
        base/数据类型.cpp
        base/sizeof关键字.cpp base/lambda表达式.cpp)
