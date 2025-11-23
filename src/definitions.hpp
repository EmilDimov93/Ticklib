// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#pragma once

struct Position2
{
    float x;
    float y;

    Position2() : x(0), y(0) {}
    Position2(float newX, float newY) : x(newX), y(newY) {}
};

struct Position3
{
    float x;
    float y;
    float z;

    Position3() : x(0), y(0), z(0) {}
    Position3(float newX, float newY, float newZ) : x(newX), y(newY), z(newZ) {}
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

struct Vec4
{
    float x;
    float y;
    float z;
    float w;

    Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4(float newX, float newY, float newZ, float newW) : x(newX), y(newY), z(newZ), w(newW) {}
};