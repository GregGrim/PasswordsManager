cmake_minimum_required(VERSION 3.24)
project(PasswordManagerProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(PasswordManagerProject main.cpp password.cpp password.h timestamp.cpp timestamp.h)
