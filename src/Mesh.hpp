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
    uint32_t color;

    std::string name;

    Mesh()
        : position{0, 0, 0}, color(0xFFFFFFFF), name("")
    {
    }

    Mesh(const std::vector<Triangle> &t,
         const Position3 &pos = {0, 0, 0},
         uint32_t col = 0xFFFFFFFF,
         const std::string &n = "")
        : tris(t), position(pos), color(col), name(n)
    {
    }
};