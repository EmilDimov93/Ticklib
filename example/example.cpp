// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

// Create a simple scene with Ticklib
// All .obj files are from https://groups.csail.mit.edu/graphics/classes/6.837/F03/models/

#include "ticklib.hpp"

int main()
{
    // Initialize a 600x300 pixel window
    tlInit(600, 300);

    // Add meshes at specified positions with colors
    tlAddMesh("../../cube.obj", {0, -0.5f, -7}, COLOR_BROWN);
    tlAddMesh("../../teapot.obj", {0, -0.1f, -7}, COLOR_GRAY);
    tlAddMesh("../../cow.obj", {-2, -0.1f, -7}, COLOR_PURPLE);

    // Scale meshes by filename
    tlScaleMesh("teapot.obj", 0.1f);
    tlScaleMesh("cube.obj", 0.4f);
    tlScaleMesh("cow.obj", 0.25f);

    // Rotate the teapot mesh around the Y-axis
    tlRotateMesh("teapot.obj", {0, 0.5f, 0});

    // Main render loop
    while (tlWindowOpen())
    {
        // Clear the screen with a light blue background
        tlClearBackground(COLOR_LIGHT_BLUE);

        // Draw all meshes with filled triangles
        tlDrawMeshes(true);
    }
    // Cleans up automatically

    return 0;
}