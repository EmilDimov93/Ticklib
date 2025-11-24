// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Core.hpp"
#include <iostream>

int main()
{
    Init(1000, 1000);

    addMesh("teapot.obj", {0, 1, 0}, COLOR_GRAY);
    addMesh("cube.obj", {0, 0, 0}, COLOR_BROWN);

    while (WindowOpen())
    {
        ClearBackground(COLOR_WHITE);

        DrawMeshes();
    }
}