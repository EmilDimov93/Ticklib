// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Core.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#define WIDTH 1000
#define HEIGHT 1000

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
            float x, y, z;
            ss >> x >> y >> z;
            vertices.push_back(Position3(x, y, z));
        }
        else if (prefix == "f")
        {
            int idx[3];
            for (int i = 0; i < 3; i++)
            {
                std::string vert;
                ss >> vert;
                size_t slash = vert.find('/');
                if (slash != std::string::npos)
                    vert = vert.substr(0, slash);
                idx[i] = std::stoi(vert) - 1;
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

    std::vector<Triangle> tris;
    if (!loadOBJ("cube.obj", tris))
    {
        std::cerr << "Failed to load model" << std::endl;
    }

    Mesh mesh1(tris, {0, 0, 0}, COLOR_GREEN);

    tris.clear();
    if (!loadOBJ("teapot.obj", tris))
    {
        std::cerr << "Failed to load model" << std::endl;
    }

    Mesh mesh2(tris, {0, 0, 0}, COLOR_PINK);

    std::vector<Mesh> meshes;
    meshes.push_back(mesh1);
    meshes.push_back(mesh2);
    DrawManager DM(meshes);

    Camera camera;

    InputManager input;

    while (WindowOpen())
    {
        input.refresh();

        DM.meshes[1].position.z -= 0.01f;

        camera.updateState(&input);

        ClearBackground((int)COLOR_BLACK);

        DM.DrawMeshes(camera);
    }
}