// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#pragma once

#include <functional>
#include <string>

#include "colors.hpp"
#include "definitions.hpp"

void Init(Size2 windowSize);

bool WindowOpen();

void ClearBackground(uint32_t color);

void DrawLine(int x1, int y0, int x2, int y2, int color);