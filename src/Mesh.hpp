// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include <vector>

#include "definitions.hpp"

class Mesh{
private:
    

public:
    std::vector<Triangle> tris;
    Position3 position;
    uint32_t color;

    Mesh() : position{0,0,0}, color(0xFFFFFFFF) {}

    Mesh(const std::vector<Triangle>& t, const Position3& pos = {0,0,0}, uint32_t col = 0xFFFFFFFF) : tris(t), position(pos), color(col) {}
};