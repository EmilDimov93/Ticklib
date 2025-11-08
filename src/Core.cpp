#include "Core.hpp"

#include <windows.h>
#include <cstdint>

#include <iostream>

HWND hwnd;

#define WIDTH 800
#define HEIGHT 600

static uint32_t pixels[WIDTH * HEIGHT];

void DrawRectangle(int x, int y, int w, int h, int color, float roundness)
{
    if (roundness < 0.0f){
        roundness = 0.0f;
    }
    if (roundness > 1.0f){
        roundness = 1.0f;
    }

    float rx = roundness * (w / 2.0f);
    float ry = roundness * (h / 2.0f);
    float rx2 = rx * rx;
    float ry2 = ry * ry;

    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            bool skip = false;

            if (i < x + rx && j < y + ry)
            {
                float dx = (x + rx) - i;
                float dy = (y + ry) - j;
                skip = (dx * dx) / (rx2) + (dy * dy) / (ry2) > 1.0f;
            }
            else if (i >= x + w - rx && j < y + ry)
            {
                float dx = i - (x + w - rx - 1);
                float dy = (y + ry) - j;
                skip = (dx * dx) / (rx2) + (dy * dy) / (ry2) > 1.0f;
            }
            else if (i < x + rx && j >= y + h - ry)
            {
                float dx = (x + rx) - i;
                float dy = j - (y + h - ry - 1);
                skip = (dx * dx) / (rx2) + (dy * dy) / (ry2) > 1.0f;
            }
            else if (i >= x + w - rx && j >= y + h - ry)
            {
                float dx = i - (x + w - rx - 1);
                float dy = j - (y + h - ry - 1);
                skip = (dx * dx) / (rx2) + (dy * dy) / (ry2) > 1.0f;
            }

            if (!skip){
                pixels[j * WIDTH + i] = color;
            }
        }
    }
}

void ClearBackground()
{
    for (int i = 0; i < WIDTH * HEIGHT; ++i)
    {
        pixels[i] = COLOR_BLUE;
    }
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
        bmi.bmiHeader.biWidth = WIDTH;
        bmi.bmiHeader.biHeight = -HEIGHT;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;

        StretchDIBits(hdc, 0, 0, WIDTH, HEIGHT,
                      0, 0, WIDTH, HEIGHT,
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
        if (msg.message == WM_QUIT)
            return false;
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    InvalidateRect(hwnd, nullptr, FALSE);

    count++;
    if (GetTickCount() - start >= 1000)
    {
        printf("One second later: %d\n", count);
        start = GetTickCount();
        count = 0;
    }

    SetCursor(cursor);

    return true;
}

void Init()
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    WNDCLASSA wc{};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Ticklib";

    RegisterClassA(&wc);

    hwnd = CreateWindowExA(
        0, "Ticklib", "Ticklib",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        WIDTH, HEIGHT, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hwnd, SW_SHOWDEFAULT);

    ClearBackground();
    cursor = LoadCursor(nullptr, IDC_ARROW);
    start = GetTickCount();
}