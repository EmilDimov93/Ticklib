// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Core.hpp"

#include <windows.h>
#include <cstdint>
#include <iostream>

HWND hwnd;

Size2 screenSize = {1000, 1000};

static uint32_t pixels[1000 * 1000];

struct Vec3 {
    float x, y, z;
};

void DrawLine(int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        if (x1 >= 0 && x1 < screenSize.w && y1 >= 0 && y1 < screenSize.h)
            pixels[y1 * screenSize.w + x1] = color;

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

void DrawRectangle(int x, int y, int w, int h, int color, float roundness)
{
    if (x >= screenSize.w || y >= screenSize.h) return;

    if (roundness < 0.0f) roundness = 0.0f;
    if (roundness > 1.0f) roundness = 1.0f;

    int rx = (int)(roundness * (w / 2.0f));
    int ry = (int)(roundness * (h / 2.0f));
    int rx2 = rx * rx;
    int ry2 = ry * ry;

    for (int j = y; j < y + h; j++)
    {
        if (j < 0 || j >= screenSize.h) continue;

        for (int i = x; i < x + w; i++)
        {
            if (i < 0 || i >= screenSize.w) continue;

            bool skip = false;

            // Top-left corner
            if (i < x + rx && j < y + ry)
            {
                int dx = (x + rx) - i;
                int dy = (y + ry) - j;
                skip = (dx * dx) / rx2 + (dy * dy) / ry2 > 1;
            }
            // Top-right corner
            else if (i >= x + w - rx && j < y + ry)
            {
                int dx = i - (x + w - rx - 1);
                int dy = (y + ry) - j;
                skip = (dx * dx) / rx2 + (dy * dy) / ry2 > 1;
            }
            // Bottom-left corner
            else if (i < x + rx && j >= y + h - ry)
            {
                int dx = (x + rx) - i;
                int dy = j - (y + h - ry - 1);
                skip = (dx * dx) / rx2 + (dy * dy) / ry2 > 1;
            }
            // Bottom-right corner
            else if (i >= x + w - rx && j >= y + h - ry)
            {
                int dx = i - (x + w - rx - 1);
                int dy = j - (y + h - ry - 1);
                skip = (dx * dx) / rx2 + (dy * dy) / ry2 > 1;
            }

            if (!skip)
                pixels[j * screenSize.w + i] = color;
        }
    }
}

void DrawRectangle(Position2 position, Size2 size, int color, float roundness)
{
    DrawRectangle((int)position.x, (int)position.y, size.w, size.h, color, roundness);
}

void ClearBackground(uint32_t color)
{
    for (int i = 0; i < screenSize.w * screenSize.h; ++i)
        pixels[i] = color;
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            BITMAPINFO bmi{};
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = screenSize.w;
            bmi.bmiHeader.biHeight = -screenSize.h;
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 32;
            bmi.bmiHeader.biCompression = BI_RGB;

            StretchDIBits(hdc, 0, 0, screenSize.w, screenSize.h,
                          0, 0, screenSize.w, screenSize.h,
                          pixels, &bmi, DIB_RGB_COLORS, SRCCOPY);

            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProcA(hwnd, msg, wp, lp);
    }
}

int count = 0;
DWORD start = 0;
HCURSOR cursor;

bool WindowOpen()
{
    MSG msg{};
    while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) return false;
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    InvalidateRect(hwnd, nullptr, FALSE);

    count++;
    if (GetTickCount() - start >= 1000)
    {
        printf("Frames this second: %d\n", count);
        start = GetTickCount();
        count = 0;
    }

    SetCursor(cursor);
    return true;
}

void Init(Size2 windowSize)
{
    screenSize.w = windowSize.w;
    screenSize.h = windowSize.h;

    HINSTANCE hInstance = GetModuleHandle(nullptr);

    WNDCLASSA wc{};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Ticklib";

    RegisterClassA(&wc);

    hwnd = CreateWindowExA(
        0, "Ticklib", "Ticklib",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        screenSize.w, screenSize.h, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hwnd, SW_SHOWDEFAULT);

    ClearBackground(COLOR_BLACK);
    cursor = LoadCursor(nullptr, IDC_ARROW);
    start = GetTickCount();
}
