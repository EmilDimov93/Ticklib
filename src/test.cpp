// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Core.hpp"
#include <iostream>

#define WIDTH 1000
#define HEIGHT 1000

#define zFar 1000
#define zNear 1

#define f 1

#define playerSpeed 5.0f

int main()
{
    Init({1000, 1000});

    int x = 100;
    int y = 100;
    int z = 5;

    Position3 startP[4] = {{-50, -50, 1}, {50, -50, 1}, {-50, 50, 1}};

    Position3 playerPos = {0, 0, -10};

    Position2 camOff = {-500, -500};

    while (WindowOpen())
    {
        //Position2 mousePos = GetMousePosition();

        //float delta = GetFrameTime();

        /*if (IsKeyDown(KEY_W)) playerPos.z += playerSpeed * delta;
        if (IsKeyDown(KEY_S)) playerPos.z -= playerSpeed * delta;
        if (IsKeyDown(KEY_A)) playerPos.x -= playerSpeed * delta;
        if (IsKeyDown(KEY_D)) playerPos.x += playerSpeed * delta;*/

        //printf("%f %f\n", playerPos.x, playerPos.z);

        /*if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            camOff.x += GetMouseDelta().x;
            camOff.y += GetMouseDelta().y;
        }*/

        Position3 P[3];

        for (int i = 0; i < 3; i++)
        {
            if (startP[i].z + f <= playerPos.z)
            {
                P[i].x = 100000;
                continue;
            }
            P[i].x = ((startP[i].x - playerPos.x) * f) / (startP[i].z - playerPos.z + f) - camOff.x;
            P[i].y = ((startP[i].y - playerPos.y) * f) / (startP[i].z - playerPos.z + f) - camOff.y;
        }

        ClearBackground();

        DrawLine(P[0].x, P[0].y, P[1].x, P[1].y, COLOR_RED);
        DrawLine(P[1].x, P[1].y, P[2].x, P[2].y, COLOR_RED);
        DrawLine(P[2].x, P[2].y, P[0].x, P[0].y, COLOR_RED);


        /*DrawRectangle(Position2(100 / 6, 100 / 6), Size2(100, 100), COLOR_RED, 0.5f);
        DrawLine(150, 100, 200, 100, COLOR_YELLOW);*/
    }
}