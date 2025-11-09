#include "Core.hpp"

#include <windows.h>
#include <cstdint>

#include <iostream>

HWND hwnd;

Size screenSize = {1200, 600};

static uint32_t pixels[1200 * 600];

void DrawRectangle(int x, int y, int w, int h, int color, float roundness)
{
    if (x > screenSize.w || y > screenSize.h)
    {
        return;
    }

    if (roundness < 0.0f)
    {
        roundness = 0.0f;
    }
    if (roundness > 1.0f)
    {
        roundness = 1.0f;
    }

    float rx = roundness * (w / 2.0f);
    float ry = roundness * (h / 2.0f);
    float rx2 = rx * rx;
    float ry2 = ry * ry;

    for (int j = y; j < y + h; j++)
    {
        if (j < 0 || j >= screenSize.h)
            continue;

        for (int i = x; i < x + w; i++)
        {
            bool skip = false;

            if (i < 0 || i >= screenSize.w)
                continue;

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

            if (!skip)
            {
                pixels[j * screenSize.w + i] = color;
            }
        }
    }
}

void DrawRectangle(Position position, Size size, int color, float roundness)
{
    DrawRectangle(position.x, position.y, size.w, size.h, color, roundness);
}

void DrawButton(Button button)
{
    DrawRectangle(
        (int)button.position.x,
        (int)button.position.y,
        (int)button.size.w,
        (int)button.size.h,
        button.paddingColor,
        button.paddingRoundness);

    DrawRectangle(
        (int)(button.position.x + button.padding),
        (int)(button.position.y + button.padding),
        (int)(button.size.w - button.padding * 2),
        (int)(button.size.h - button.padding * 2),
        button.backgroundColor,
        button.roundness);
}

void ClearBackground()
{
    for (int i = 0; i < screenSize.w * screenSize.h; ++i)
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
        if (msg.message == WM_QUIT)
            return false;
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
        screenSize.w, screenSize.h, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hwnd, SW_SHOWDEFAULT);

    ClearBackground();
    cursor = LoadCursor(nullptr, IDC_ARROW);
    start = GetTickCount();
}