cmake_minimum_required(VERSION 3.10)
project(Ticklib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Ticklib
    src/test.cpp
    src/Core.cpp
)

target_link_libraries(Ticklib
    user32
    gdi32
)