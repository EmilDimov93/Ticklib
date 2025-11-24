// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Core.hpp"
#include <iostream>

#define WIDTH 1000
#define HEIGHT 1000

#define zFar 1000
#define zNear 1

#define fov 60
#define f 1.0f / tanf(fov * 0.5f * (PI / 180.0f))

#define aspectRatio 1

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

    Camera camera;

    InputManager input;

    while (WindowOpen())
    {
        input.refresh();
        Position2 mousePos = input.getMousePos();

        camera.updateState(&input);

        ClearBackground((int)COLOR_BLACK);

        for (Triangle tri : mesh.tris)
        {
            Vec4 viewP[3];
            for (int i = 0; i < 3; i++)
            {
                Position3 p = {tri.vertices[i].x - camera.x(),
                               tri.vertices[i].y - camera.y(),
                               tri.vertices[i].z - camera.z()};

                viewP[i].x = p.x * camera.getRight().x + p.y * camera.getRight().y + p.z * camera.getRight().z;
                viewP[i].y = p.x * camera.getUp().x + p.y * camera.getUp().y + p.z * camera.getUp().z;
                viewP[i].z = p.x * camera.getForward().x + p.y * camera.getForward().y + p.z * camera.getForward().z;
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