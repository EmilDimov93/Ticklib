// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include <vector>
#include <string>

#include "definitions.hpp"

class Mesh
{
private:
public:
    std::vector<Triangle> tris;
    Position3 position;

    std::string name;

    Mesh()
        : position{0, 0, 0}, name("")
    {
    }

    Mesh(const std::vector<Triangle> &t,
         const Position3 &pos = {0, 0, 0},
         const std::string &n = "")
        : tris(t), position(pos), name(n)
    {
    }
};

void MoveMesh(uint32_t index, Position3 delta);
void MoveMesh(std::string name, Position3 delta);

void RotateMesh(uint32_t index, Rotation3 rotation);
void RotateMesh(std::string name, Rotation3 rotation);

void ScaleMesh(uint32_t index, Scale3 scale);
void ScaleMesh(std::string name, Scale3 scale);
void ScaleMesh(uint32_t index, float scale);
void ScaleMesh(std::string name, float scale);