project(test)

set(CMAKE_CXX_STANDARD 11)

cmake_minimum_required(VERSION 3.0)

include_directories(include/)

add_executable(app src/main.cpp src/account.cpp)

