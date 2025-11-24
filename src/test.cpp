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

int main()
{
    Init({WIDTH, HEIGHT});

    std::vector<Triangle> list;
    if (!loadOBJ("teapot.obj", list))
    {
        std::cerr << "Failed to load model" << std::endl;
    }
    else{
        std::cout << "Good";
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

            bool behind = false;
            for (int i = 0; i < 3; i++)
            {
                if (viewP[i].z <= 0)
                {
                    behind = true;
                    break;
                }
            }
            if (behind)
            {
                continue;
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

            DrawLine((int)screenP[0].x, (int)screenP[0].y, (int)screenP[1].x, (int)screenP[1].y, COLOR_RED);
            DrawLine((int)screenP[1].x, (int)screenP[1].y, (int)screenP[2].x, (int)screenP[2].y, COLOR_RED);
            DrawLine((int)screenP[2].x, (int)screenP[2].y, (int)screenP[0].x, (int)screenP[0].y, COLOR_RED);
        }
    }
}