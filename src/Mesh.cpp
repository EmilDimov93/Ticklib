// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Mesh.hpp"

#include <iostream>

extern std::vector<Mesh> meshes;

void MoveMesh(uint32_t index, Position3 delta)
{
    for (Triangle& tri : meshes[index].tris)
    {
        for (Position3& vertice : tri.vertices)
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
    for (const Mesh& mesh : meshes)
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

// Euler angle rotation formula
void RotateMesh(uint32_t index, Rotation3 rotation)
{
    float cp = cosf(rotation.pitch), sp = sinf(rotation.pitch);
    float cy = cosf(rotation.yaw), sy = sinf(rotation.yaw);
    float cr = cosf(rotation.roll), sr = sinf(rotation.roll);

    for (Triangle& tri : meshes[index].tris)
    {
        for (Position3& v : tri.vertices)
        {
            float x = v.x;
            float y = v.y;
            float z = v.z;

            float y1 = y * cp - z * sp;
            float z1 = y * sp + z * cp;

            float x2 = x * cy + z1 * sy;
            float z2 = -x * sy + z1 * cy;

            float x3 = x2 * cr - y1 * sr;
            float y3 = x2 * sr + y1 * cr;

            v.x = x3;
            v.y = y3;
            v.z = z2;
        }
    }
}

void RotateMesh(std::string name, Rotation3 rotation)
{
    int i = 0;
    for (const Mesh& mesh : meshes)
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
    for (Triangle& tri : meshes[index].tris)
    {
        for (Position3& vertice : tri.vertices)
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
    for (const Mesh& mesh : meshes)
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