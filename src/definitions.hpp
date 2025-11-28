// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#pragma once

#include <cstdint>

#define PI 3.1415927f

#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0xFF000000
#define COLOR_RED 0xFFFF0000
#define COLOR_GREEN 0xFF00FF00
#define COLOR_BLUE 0xFF0000FF
#define COLOR_LIGHT_BLUE 0xFFA0C8FF
#define COLOR_YELLOW 0xFFFFFF00
#define COLOR_CYAN 0xFF00FFFF
#define COLOR_MAGENTA 0xFFFF00FF
#define COLOR_ORANGE 0xFFFFA500
#define COLOR_PURPLE 0xFF800080
#define COLOR_PINK 0xFFFF69B4
#define COLOR_BROWN 0xFF8B4513
#define COLOR_GRAY 0xFF808080
#define COLOR_LIGHT_GRAY 0xFFD3D3D3
#define COLOR_DARK_GRAY 0xFF404040

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

struct Scale3
{
    float x;
    float y;
    float z;

    Scale3() : x(0), y(0), z(0) {}
    Scale3(float newX, float newY, float newZ) : x(newX), y(newY), z(newZ) {}
};

struct Rotation2
{
    float pitch;
    float yaw;

    Rotation2() : pitch(0), yaw(0) {}
    Rotation2(float newPitch, float newYaw) : pitch(newPitch), yaw(newYaw) {}
};

struct Rotation3
{
    float pitch;
    float yaw;
    float roll;

    Rotation3() : pitch(0), yaw(0), roll(0) {}
    Rotation3(float newPitch, float newYaw, float newRoll) : pitch(newPitch), yaw(newYaw), roll(newRoll) {}
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

struct Triangle
{
    Position3 vertices[3];
    uint32_t color;

    Triangle()
        : vertices{Position3(), Position3(), Position3()}, color(COLOR_GRAY)
    {}

    Triangle(const Position3& a,
             const Position3& b,
             const Position3& c,
             uint32_t col)
        : vertices{ a, b, c }, color(col)
    {}
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