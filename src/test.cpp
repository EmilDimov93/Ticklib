// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Core.hpp"

int main()
{
    Init(1000, 1000);

    AddMesh("teapot.obj", {0, 1, 0}, COLOR_GRAY);
    AddMesh("cube.obj", {0, 0, 0}, COLOR_BROWN);

    ScaleMesh("teapot.obj", {0.5f, 0.5f, 0.5f});

    while (WindowOpen())
    {
        ClearBackground(COLOR_WHITE);

        DrawMeshes();
    }
}