// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#pragma once

#include <string>

#include "InputManager.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "colors.hpp"
#include "definitions.hpp"

void Init(int windowWidth, int windowHeight);

bool WindowOpen();

void ClearBackground(uint32_t color);

uint16_t GetFps();

void AddMesh(std::string fileName, Position3 position, uint32_t color);

void MoveMesh(uint32_t index, Position3 delta);
void MoveMesh(std::string name, Position3 delta);

void ScaleMesh(uint32_t index, Scale3 scale);
void ScaleMesh(std::string name, Scale3 scale);
void ScaleMesh(uint32_t index, float scale);
void ScaleMesh(std::string name, float scale);

void DrawMeshes();

void setZFar(float newZFar);