// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Mesh.hpp"

#include <iostream>

extern std::vector<Mesh> meshes;

void MoveMesh(uint32_t index, Position3 deltaPos)
{
    for (Triangle& tri : meshes[index].tris)
    {
        for (Position3& vertice : tri.vertices)
        {
            vertice.x += deltaPos.x;
            vertice.y += deltaPos.y;
            vertice.z += deltaPos.z;
        }
    }
}

void MoveMesh(std::string name, Position3 deltaPos)
{
    int i = 0;
    for (const Mesh& mesh : meshes)
    {
        if (mesh.name == name)
        {
            MoveMesh(i, deltaPos);
            return;
        }
        i++;
    }

    std::cerr << "Couldn't find mesh: " << name << std::endl;
}

// Euler angle rotation formula
void RotateMesh(uint32_t index, Rotation3 deltaRot)
{
    float cp = cosf(deltaRot.pitch), sp = sinf(deltaRot.pitch);
    float cy = cosf(deltaRot.yaw), sy = sinf(deltaRot.yaw);
    float cr = cosf(deltaRot.roll), sr = sinf(deltaRot.roll);

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

void RotateMesh(std::string name, Rotation3 deltaRot)
{
    int i = 0;
    for (const Mesh& mesh : meshes)
    {
        if (mesh.name == name)
        {
            RotateMesh(i, deltaRot);
            return;
        }
        i++;
    }

    std::cerr << "Couldn't find mesh: " << name << std::endl;
}

void ScaleMesh(uint32_t index, Scale3 deltaScale)
{
    for (Triangle& tri : meshes[index].tris)
    {
        for (Position3& vertice : tri.vertices)
        {
            vertice.x *= deltaScale.x;
            vertice.y *= deltaScale.y;
            vertice.z *= deltaScale.z;
        }
    }
}

void ScaleMesh(std::string name, Scale3 deltaScale)
{
    int i = 0;
    for (const Mesh& mesh : meshes)
    {
        if (mesh.name == name)
        {
            ScaleMesh(i, deltaScale);
            return;
        }
        i++;
    }

    std::cerr << "Couldn't find mesh: " << name << std::endl;
}

void ScaleMesh(uint32_t index, float deltaUniformScale)
{
    ScaleMesh(index, {deltaUniformScale, deltaUniformScale, deltaUniformScale});
}

void ScaleMesh(std::string name, float deltaUniformScale)
{
    ScaleMesh(name, {deltaUniformScale, deltaUniformScale, deltaUniformScale});
}