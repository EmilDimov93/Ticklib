// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#pragma once

#include <functional>
#include <string>

#include "InputManager.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "colors.hpp"
#include "definitions.hpp"

void Init(Size2 windowSize);

bool WindowOpen();

void ClearBackground(uint32_t color);

void DrawLine(int x1, int y0, int x2, int y2, int color);

void DrawFilledTriangle(const Position2& p0, const Position2& p1, const Position2& p2, int color);

class DrawManager{
public:
    std::vector<Mesh> meshes;

    DrawManager() = default;

    DrawManager(const std::vector<Mesh>& m) : meshes(m) {}

    void DrawMeshes(Camera camera);
};