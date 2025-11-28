// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "ticklib.hpp"
#include "iostream"

int main()
{
    tlInit(1000, 1000);

    tlAddMesh("cube.obj", {0, -0.5f, -7}, COLOR_BROWN);
    tlAddMesh("teapot.obj", {0, -0.1f, -7}, COLOR_GRAY);
    tlAddMesh("cow.obj", {-2, -0.1f, -7}, COLOR_PURPLE);

    tlScaleMesh("teapot.obj", 0.1f);
    tlScaleMesh("cube.obj", 0.4f);
    tlScaleMesh("cow.obj", 0.25f);

    tlRotateMesh("teapot.obj", {0, 0.5f, 0});

    while (tlWindowOpen())
    {
        tlClearBackground(COLOR_LIGHT_BLUE);

        tlDrawMeshes(false);
    }
}