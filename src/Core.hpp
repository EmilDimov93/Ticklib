// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#pragma once

#include <string>

#include "InputManager.hpp"
#include "definitions.hpp"
#include "Mesh.hpp"

void Init(int windowWidth, int windowHeight);

bool WindowOpen();

void ClearBackground(uint32_t color);

uint16_t GetFps();

void AddMesh(std::string fileName, Position3 position, uint32_t color);

void DrawMeshes(bool trianglesFilled);

void setCameraSpeed(float newSpeed);

void setFov(int newFov);