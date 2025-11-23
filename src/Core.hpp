// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#pragma once

#include <functional>
#include <string>

#include "colors.hpp"
#include "definitions.hpp"

void Init(Size2 windowSize);

bool WindowOpen();

void ClearBackground();

void DrawLine(int x1, int y0, int x2, int y2, int color);

void DrawRectangle(int x, int y, int w, int h, int color, float roundness = 0);

void DrawRectangle(Position2 position, Size2 size, int color, float roundness = 0);