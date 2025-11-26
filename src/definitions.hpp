// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#pragma once

#define PI 3.1415927f

#define zNear 0.01f
#define fov 60
#define speed 5.0f

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

    Triangle()
        : vertices{ Position3(), Position3(), Position3() }
    {}

    Triangle(const Position3& a,
             const Position3& b,
             const Position3& c)
        : vertices{ a, b, c }
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