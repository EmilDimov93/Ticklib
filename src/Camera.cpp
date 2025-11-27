// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Camera.hpp"

#include <cmath>

using std::cosf;
using std::sinf;

#include "InputManager.hpp"

float speed = 5.0f;

void Camera::setSpeed(float newSpeed){
    speed = newSpeed;
}

float Camera::x()
{
    return position.x;
}

float Camera::y()
{
    return position.y;
}

float Camera::z()
{
    return position.z;
}

Position3 Camera::getForward()
{
    return forward;
}

Position3 Camera::getRight()
{
    return right;
}

Position3 Camera::getUp()
{
    return up;
}

void Camera::updateState()
{
    // Frame delta
    static LARGE_INTEGER frequency;
    static LARGE_INTEGER lastTime;
    static bool timeInitialized = false;

    if (!timeInitialized)
    {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&lastTime);
        timeInitialized = true;
    }

    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    float delta = (float)(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;
    lastTime = currentTime;

    // Mouse delta
    static POINT lastMousePos = {0, 0};
    static bool mouseInitialized = false;

    POINT p;
    GetCursorPos(&p);

    Position2 md = {0, 0};
    if (mouseInitialized)
    {
        md.x = (float)p.x - (float)lastMousePos.x;
        md.y = (float)p.y - (float)lastMousePos.y;
    }
    else
    {
        mouseInitialized = true;
    }
    lastMousePos = p;

    float cs = cosf(rotation.pitch);
    float sn = sinf(rotation.pitch);

    if (tlIsDown(TL_KEY_W))
    {
        position.x += sn * speed * delta;
        position.z += cs * speed * delta;
    }
    if (tlIsDown(TL_KEY_S))
    {
        position.x -= sn * speed * delta;
        position.z -= cs * speed * delta;
    }

    if (tlIsDown(TL_KEY_A))
    {
        position.x += cs * speed * delta;
        position.z -= sn * speed * delta;
    }
    if (tlIsDown(TL_KEY_D))
    {
        position.x -= cs * speed * delta;
        position.z += sn * speed * delta;
    }

    if (tlIsDown(TL_MOUSE_BTN_LEFT))
    {
        rotation.pitch -= md.x * 0.01f;
        rotation.yaw -= md.y * 0.01f;

        if (rotation.yaw > 1.5f)
            rotation.yaw = 1.5f;
        if (rotation.yaw < -1.5f)
            rotation.yaw = -1.5f;
    }

    forward = {
        cosf(rotation.yaw) * sinf(rotation.pitch),
        sinf(rotation.yaw),
        cosf(rotation.yaw) * cosf(rotation.pitch)};
    right = {
        cosf(rotation.pitch),
        0,
        -sinf(rotation.pitch)};
    up = {
        right.y * forward.z - right.z * forward.y,
        right.z * forward.x - right.x * forward.z,
        right.x * forward.y - right.y * forward.x};
}