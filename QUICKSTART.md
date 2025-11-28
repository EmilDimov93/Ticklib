# Quick Start With Ticklib

Refer to example folder for best results

### Requirements:
- Windows computer

## 1. Download files

Download the latest release

## 2. File structure

Create your project folder and follow this structure:
```
MyProgram/
├─ include/
│  └─ ticklib.hpp
├─ lib/
│  └─ Ticklib.lib
├─ myProgram.cpp
└─ CMakeLists.txt
```

## 3. CMake

In your project folder, create a CMakeLists.txt file

#### Example:
```cmake
cmake_minimum_required(VERSION 3.10)
project(Example)

add_executable(example example.cpp)

target_include_directories(example PRIVATE "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(example PRIVATE "${CMAKE_SOURCE_DIR}/lib/Ticklib.lib" user32 gdi32)
```

Then run these commands in powershell:
```shell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## 4. Code

The minimal code you need to create a window is:

```cpp
#include "ticklib.hpp"

int main()
{
    tlInit(600, 300);

    while(tlWindowOpen())
    {
        tlClearBackground(COLOR_BLACK);
    }
}
```

Refer to DOCS.md to learn how to add your first mesh!