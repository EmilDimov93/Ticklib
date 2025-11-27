// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#pragma once

#include <string>

#include "InputManager.hpp"
#include "definitions.hpp"
#include "Mesh.hpp"

#define TL_DEFAULT_CAMERA_SPEED 5.0f
#define TL_DEFAULT_FOV 60

void tlInit(int windowWidth, int windowHeight);

bool tlWindowOpen();

void tlClearBackground(uint32_t color);

uint16_t tlGetFps();

void tlAddMesh(std::string fileName, Position3 position, uint32_t color);

void tlDrawMeshes(bool trianglesFilled);

void tlSetCameraSpeed(float newSpeed);

void tlSetFov(int newFov);