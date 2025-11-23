// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#pragma once

struct Position2
{
    int x;
    int y;

    Position2() : x(0), y(0) {}
    Position2(int newX, int newY) : x(newX), y(newY) {}
};

struct Position3
{
    int x;
    int y;
    int z;

    Position3() : x(0), y(0), z(0) {}
    Position3(int newX, int newY, int newZ) : x(newX), y(newY), z(newZ) {}
};

struct Size2
{
    int w;
    int h;

    Size2() : w(0), h(0) {}
    Size2(int newW, int newH) : w(newW), h(newH) {}
};

struct Size3
{
    int w;
    int h;
    int d;

    Size3() : w(0), h(0), d(0) {}
    Size3(int newW, int newH, int newD) : w(newW), h(newH), d(newD) {}
};