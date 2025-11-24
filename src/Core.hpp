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

extern std::vector<Mesh> meshes;

bool loadOBJ(const std::string &filename, std::vector<Triangle> &outTriangles);

void Init(int windowWidth, int windowHeight);

bool WindowOpen();

void ClearBackground(uint32_t color);

void DrawLine(int x1, int y0, int x2, int y2, int color);

void DrawFilledTriangle(const Position2& p0, const Position2& p1, const Position2& p2, int color);

uint16_t GetFps();

void addMesh(std::string fileName, Position3 position, uint32_t color);

void scaleMesh(uint32_t index, float scale);
void scaleMesh(std::string name, float scale);

void DrawMeshes();