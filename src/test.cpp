// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Core.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#define WIDTH 1000
#define HEIGHT 1000

#define zFar 1000
#define zNear 1

#define fov 60
#define f 1.0f / tanf(fov * 0.5f * (PI / 180.0f))

#define aspectRatio 1

bool loadOBJ(const std::string &filename, std::vector<Triangle> &outTriangles)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open OBJ file: " << filename << std::endl;
        return false;
    }

    std::vector<Position3> vertices;
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v")
        {
            // Vertex
            float x, y, z;
            ss >> x >> y >> z;
            vertices.push_back(Position3(x, y, z));
        }
        else if (prefix == "f")
        {
            // Face (triangle)
            int idx[3];
            for (int i = 0; i < 3; i++)
            {
                std::string vert;
                ss >> vert;
                size_t slash = vert.find('/');
                if (slash != std::string::npos)
                    vert = vert.substr(0, slash); // ignore texture/normal
                idx[i] = std::stoi(vert) - 1;     // OBJ indices start at 1
            }
            outTriangles.push_back(Triangle(
                vertices[idx[0]],
                vertices[idx[1]],
                vertices[idx[2]]));
        }
    }

    return true;
}

void convertTriToView(Triangle tri, Camera camera, Vec4 out[3])
{
    for (int i = 0; i < 3; i++)
    {
        Position3 p = {tri.vertices[i].x - camera.x(),
                       tri.vertices[i].y - camera.y(),
                       tri.vertices[i].z - camera.z()};

        out[i].x = p.x * camera.getRight().x + p.y * camera.getRight().y + p.z * camera.getRight().z;
        out[i].y = p.x * camera.getUp().x + p.y * camera.getUp().y + p.z * camera.getUp().z;
        out[i].z = p.x * camera.getForward().x + p.y * camera.getForward().y + p.z * camera.getForward().z;
        out[i].w = 1;
    }
}

bool isTriInView(Vec4 viewP[3])
{
    for (int i = 0; i < 3; i++)
    {
        if (viewP[i].z <= 0)
        {
            return false;
        }
    }

    return true;
}

void convertViewToClip(Vec4 viewP[3], Vec4 out[3])
{
    for (int i = 0; i < 3; i++)
    {
        out[i].x = viewP[i].x * f / aspectRatio;
        out[i].y = viewP[i].y * f;
        out[i].z = viewP[i].z * (zFar + zNear) / (zNear - zFar) + (2 * zFar * zNear) / (zNear - zFar);
        out[i].w = -viewP[i].z;
    }
}

void convertClipToNormalized(Vec4 clipP[3], Position3 out[3])
{
    for (int i = 0; i < 3; i++)
    {
        out[i].x = clipP[i].x / clipP[i].w;
        out[i].y = clipP[i].y / clipP[i].w;
        out[i].z = clipP[i].z / clipP[i].w;
    }
}

void convertNormalizedToScreen(Position3 normalizedP[3], Position2 out[3])
{
    for (int i = 0; i < 3; i++)
    {
        out[i].x = ((normalizedP[i].x + 1) / 2) * WIDTH;
        out[i].y = (1 - (normalizedP[i].y + 1) / 2) * HEIGHT;
    }
}

int main()
{
    Init({WIDTH, HEIGHT});

    std::vector<Triangle> list;
    if (!loadOBJ("teapot.obj", list))
    {
        std::cerr << "Failed to load model" << std::endl;
    }

    Mesh mesh(list);

    Camera camera;

    InputManager input;

    while (WindowOpen())
    {
        input.refresh();

        camera.updateState(&input);

        ClearBackground((int)COLOR_BLACK);

        for (Triangle tri : mesh.tris)
        {
            Vec4 viewP[3];
            convertTriToView(tri, camera, viewP);

            if (!isTriInView(viewP))
            {
                continue;
            }

            Vec4 clipP[3];
            convertViewToClip(viewP, clipP);

            Position3 normalizedP[3];
            convertClipToNormalized(clipP, normalizedP);

            Position2 screenP[3];
            convertNormalizedToScreen(normalizedP, screenP);

            DrawFilledTriangle(screenP[0], screenP[1], screenP[2], COLOR_BLUE);

            // DrawLine((int)screenP[0].x, (int)screenP[0].y, (int)screenP[1].x, (int)screenP[1].y, COLOR_RED);
            // DrawLine((int)screenP[1].x, (int)screenP[1].y, (int)screenP[2].x, (int)screenP[2].y, COLOR_RED);
            // DrawLine((int)screenP[2].x, (int)screenP[2].y, (int)screenP[0].x, (int)screenP[0].y, COLOR_RED);
        }
    }
}