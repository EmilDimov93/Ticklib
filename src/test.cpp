// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Core.hpp"
#include "iostream"

int main()
{
    Init(1000, 1000);

    AddMesh("cube.obj", {0, -0.5f, -7}, COLOR_BROWN);
    AddMesh("teapot.obj", {0, -0.1f, -7}, COLOR_GRAY);
    AddMesh("cow.obj", {-2, -0.1f, -7}, COLOR_PINK);

    ScaleMesh("teapot.obj", 0.1f);
    ScaleMesh("cube.obj", 0.4f);
    ScaleMesh("cow.obj", 0.25f);

    RotateMesh("teapot.obj", {0, 0.5f, 0});

    while (WindowOpen())
    {
        ClearBackground(COLOR_LIGHT_BLUE);

        DrawMeshes(true);
    }
}