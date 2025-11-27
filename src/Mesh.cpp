// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Mesh.hpp"

#include <iostream>

extern std::vector<Mesh> meshes;

void MoveMesh(uint32_t index, Position3 delta)
{
    for (Triangle &tri : meshes[index].tris)
    {
        for (Position3 &vertice : tri.vertices)
        {
            vertice.x += delta.x;
            vertice.y += delta.y;
            vertice.z += delta.z;
        }
    }
}

void MoveMesh(std::string name, Position3 delta)
{
    int i = 0;
    for (Mesh mesh : meshes)
    {
        if (mesh.name == name)
        {
            MoveMesh(i, delta);
            return;
        }
        i++;
    }

    std::cerr << "Couldn't find mesh: " << name << std::endl;
}

void RotateMesh(uint32_t index, Rotation3 rotation)
{
    float cx = cosf(rotation.pitch), sx = sinf(rotation.pitch);
    float cy = cosf(rotation.yaw), sy = sinf(rotation.yaw);
    float cz = cosf(rotation.roll), sz = sinf(rotation.roll);

    for (Triangle &tri : meshes[index].tris)
    {
        for (Position3 &v : tri.vertices)
        {
            float y1 = v.y * cx - v.z * sx;
            float z1 = v.y * sx + v.z * cx;

            float x2 = v.x * cy + z1 * sy;
            float z2 = -v.x * sy + z1 * cy;

            float x3 = x2 * cz - y1 * sz;
            float y3 = x2 * sz + y1 * cz;

            v.x = x3;
            v.y = y3;
            v.z = z2;
        }
    }
}

void RotateMesh(std::string name, Rotation3 rotation)
{
    int i = 0;
    for (Mesh mesh : meshes)
    {
        if (mesh.name == name)
        {
            RotateMesh(i, rotation);
            return;
        }
        i++;
    }

    std::cerr << "Couldn't find mesh: " << name << std::endl;
}

void ScaleMesh(uint32_t index, Scale3 scale)
{
    for (Triangle &tri : meshes[index].tris)
    {
        for (Position3 &vertice : tri.vertices)
        {
            vertice.x *= scale.x;
            vertice.y *= scale.y;
            vertice.z *= scale.z;
        }
    }
}

void ScaleMesh(std::string name, Scale3 scale)
{
    int i = 0;
    for (Mesh mesh : meshes)
    {
        if (mesh.name == name)
        {
            ScaleMesh(i, scale);
            return;
        }
        i++;
    }

    std::cerr << "Couldn't find mesh: " << name << std::endl;
}

void ScaleMesh(uint32_t index, float scale)
{
    ScaleMesh(index, {scale, scale, scale});
}

void ScaleMesh(std::string name, float scale)
{
    ScaleMesh(name, {scale, scale, scale});
}