#pragma once

#include "colors.h"

struct Position{
    int x;
    int y;

    Position(int x_, int y_) : x(x_), y(y_) {}
};

struct Size{
    int w;
    int h;

    Size(int w_, int h_) : w(w_), h(h_) {}
};

void Init();

bool WindowOpen();

void ClearBackground();

void DrawRectangle(int x, int y, int w, int h, int color, float roundness = 0);

void DrawRectangle(Position position, Size size, int color, float roundness = 0);