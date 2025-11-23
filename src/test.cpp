// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Core.hpp"
#include <iostream>

#define PI 3.1415927f

#define WIDTH 1000
#define HEIGHT 1000

#define zFar 1000
#define zNear 1

#define fov 60
#define f 1.0f / tanf(fov * 0.5f * (PI / 180.0f))

#define aspectRatio 1

#define speed 5.0f

int main()
{
    Init({1000, 1000});

    Position3 worldP[3] = {
        {-1.0f, -1.0f, 5.0f},
        {1.0f, -1.0f, 5.0f},
        {0.0f, 1.0f, 5.0f}
    };

    Position3 cameraPos = {0, 0, -10};

    Position2 cameraRot = {0, 0};

    while (WindowOpen())
    {
        //Position2 mousePos = GetMousePosition();

        /*float delta = GetFrameTime();

        float cs = cosf(cameraRot.x);
        float sn = sinf(cameraRot.x);

        if (IsKeyDown(KEY_W))
        {
            cameraPos.x += sn * speed * delta;
            cameraPos.z += cs * speed * delta;
        }
        if (IsKeyDown(KEY_S))
        {
            cameraPos.x -= sn * speed * delta;
            cameraPos.z -= cs * speed * delta;
        }

        if (IsKeyDown(KEY_A))
        {
            cameraPos.x += cs * speed * delta;
            cameraPos.z -= sn * speed * delta;
        }
        if (IsKeyDown(KEY_D))
        {
            cameraPos.x -= cs * speed * delta;
            cameraPos.z += sn * speed * delta;
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            Vector2 md = GetMouseDelta();
            cameraRot.x -= md.x * 0.01;
            cameraRot.y -= md.y * 0.01;
            if (cameraRot.y > 1.5f)
                cameraRot.y = 1.5f;
            if (cameraRot.y < -1.5f)
                cameraRot.y = -1.5f;
        }*/

        Position3 forward = {
            cosf(cameraRot.y) * sinf(cameraRot.x),
            sinf(cameraRot.y),
            cosf(cameraRot.y) * cosf(cameraRot.x)};
        Position3 right = {
            cosf(cameraRot.x),
            0,
            -sinf(cameraRot.x)};
        Position3 up = {
            right.y * forward.z - right.z * forward.y,
            right.z * forward.x - right.x * forward.z,
            right.x * forward.y - right.y * forward.x};

        Vec4 viewP[3];
        for (int i = 0; i < 3; i++)
        {
            Position3 p = {worldP[i].x - cameraPos.x,
                         worldP[i].y - cameraPos.y,
                         worldP[i].z - cameraPos.z};

            viewP[i].x = p.x * right.x + p.y * right.y + p.z * right.z;
            viewP[i].y = p.x * up.x + p.y * up.y + p.z * up.z;
            viewP[i].z = p.x * forward.x + p.y * forward.y + p.z * forward.z;
            viewP[i].w = 1;
        }

        Vec4 clipP[3];

        for (int i = 0; i < 3; i++)
        {
            clipP[i].x = viewP[i].x * f / aspectRatio;
            clipP[i].y = viewP[i].y * f;
            clipP[i].z = viewP[i].z * (zFar + zNear) / (zNear - zFar) + (2 * zFar * zNear) / (zNear - zFar);
            clipP[i].w = -viewP[i].z;
        }

        Position3 normalizedP[3];

        for (int i = 0; i < 3; i++)
        {
            normalizedP[i].x = clipP[i].x / clipP[i].w;
            normalizedP[i].y = clipP[i].y / clipP[i].w;
            normalizedP[i].z = clipP[i].z / clipP[i].w;
        }

        Position2 screenP[3];

        for (int i = 0; i < 3; i++)
        {
            screenP[i].x = ((normalizedP[i].x + 1) / 2) * WIDTH;
            screenP[i].y = (1 - (normalizedP[i].y + 1) / 2) * HEIGHT;
        }

        ClearBackground((int)COLOR_BLACK);

        DrawLine((int)screenP[0].x, (int)screenP[0].y, (int)screenP[1].x, (int)screenP[1].y, COLOR_RED);
        DrawLine((int)screenP[1].x, (int)screenP[1].y, (int)screenP[2].x, (int)screenP[2].y, COLOR_RED);
        DrawLine((int)screenP[2].x, (int)screenP[2].y, (int)screenP[0].x, (int)screenP[0].y, COLOR_RED);
    }
}