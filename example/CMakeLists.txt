cmake_minimum_required(VERSION 3.10)
project(Example)

add_executable(example example.cpp)

target_include_directories(example PRIVATE "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(example PRIVATE "${CMAKE_SOURCE_DIR}/lib/Ticklib.lib" user32 gdi32)