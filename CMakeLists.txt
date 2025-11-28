cmake_minimum_required(VERSION 3.10)
project(ticklib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ticklib STATIC
    src/ticklib.cpp
    src/InputManager.cpp
    src/Mesh.cpp
    src/Camera.cpp
)