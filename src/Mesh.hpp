// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include <vector>

#include "definitions.hpp"

class Mesh{
private:
    

public:
    std::vector<Triangle> tris;
    Position3 position;
    Mesh() = default;

    Mesh(const std::vector<Triangle>& t) : tris(t) {}
};