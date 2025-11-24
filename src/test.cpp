// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Core.hpp"
#include <iostream>

#include "InputManager.hpp"
#include "Mesh.hpp"

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
    Init({WIDTH, HEIGHT});

    Triangle t1(
        Position3(-1.0f, -1.0f, 5.0f),
        Position3(1.0f, -1.0f, 5.0f),
        Position3(0.0f, 1.0f, 5.0f));

    Triangle t2(
        Position3(0, 0, 1),
        Position3(1, 0, 1),
        Position3(0, 1, 1));

    std::vector<Triangle> list = {t1, t2};

    Mesh mesh(list);

    Position3 cameraPos = {0, 0, -10};

    Position2 cameraRot = {0, 0};

    InputManager input;

    while (WindowOpen())
    {
        input.refresh();
        Position2 mousePos = input.getMousePos();

        // Frame delta
        static LARGE_INTEGER frequency;
        static LARGE_INTEGER lastTime;
        static bool timeInitialized = false;

        if (!timeInitialized)
        {
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&lastTime);
            timeInitialized = true;
        }

        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        float delta = (float)(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;
        lastTime = currentTime;

        // Mouse delta
        static POINT lastMousePos = {0, 0};
        static bool mouseInitialized = false;

        POINT p;
        GetCursorPos(&p);

        Position2 md = {0, 0};
        if (mouseInitialized)
        {
            md.x = (float)p.x - (float)lastMousePos.x;
            md.y = (float)p.y - (float)lastMousePos.y;
        }
        else
        {
            mouseInitialized = true;
        }
        lastMousePos = p;

        float cs = cosf(cameraRot.x);
        float sn = sinf(cameraRot.x);

        if (input.isDown(TL_KEY_W))
        {
            cameraPos.x += sn * speed * delta;
            cameraPos.z += cs * speed * delta;
        }
        if (input.isDown(TL_KEY_S))
        {
            cameraPos.x -= sn * speed * delta;
            cameraPos.z -= cs * speed * delta;
        }

        if (input.isDown(TL_KEY_A))
        {
            cameraPos.x += cs * speed * delta;
            cameraPos.z -= sn * speed * delta;
        }
        if (input.isDown(TL_KEY_D))
        {
            cameraPos.x -= cs * speed * delta;
            cameraPos.z += sn * speed * delta;
        }

        if (input.isDown(TL_MOUSE_BTN_LEFT))
        {
            cameraRot.x -= md.x * 0.01f;
            cameraRot.y -= md.y * 0.01f;

            if (cameraRot.y > 1.5f)
                cameraRot.y = 1.5f;
            if (cameraRot.y < -1.5f)
                cameraRot.y = -1.5f;
        }

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

        ClearBackground((int)COLOR_BLACK);

        for (Triangle tri : mesh.tris)
        {
            Vec4 viewP[3];
            for (int i = 0; i < 3; i++)
            {
                Position3 p = {tri.vertices[i].x - cameraPos.x,
                               tri.vertices[i].y - cameraPos.y,
                               tri.vertices[i].z - cameraPos.z};

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

            bool onScreen = false;
            for (int i = 0; i < 3; i++)
            {
                if (screenP[i].x >= 0 && screenP[i].x < WIDTH && screenP[i].y >= 0 && screenP[i].y < HEIGHT)
                {
                    onScreen = true;
                    break;
                }
            }

            if (onScreen)
            {
                DrawLine((int)screenP[0].x, (int)screenP[0].y, (int)screenP[1].x, (int)screenP[1].y, COLOR_RED);
                DrawLine((int)screenP[1].x, (int)screenP[1].y, (int)screenP[2].x, (int)screenP[2].y, COLOR_RED);
                DrawLine((int)screenP[2].x, (int)screenP[2].y, (int)screenP[0].x, (int)screenP[0].y, COLOR_RED);
            }
        }
    }
}