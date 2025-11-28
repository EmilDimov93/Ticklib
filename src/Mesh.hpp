// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include <vector>

#include "ticklib.hpp"

struct Triangle
{
    Position3 vertices[3];
    uint32_t color;

    Triangle()
        : vertices{Position3(), Position3(), Position3()}, color(TlColors::Gray)
    {}

    Triangle(const Position3& a,
             const Position3& b,
             const Position3& c,
             uint32_t col)
        : vertices{ a, b, c }, color(col)
    {}
};

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