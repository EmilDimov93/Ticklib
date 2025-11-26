// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "Core.hpp"

#include <windows.h>
#include <cstdint>
#include <iostream>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <algorithm>
#include <fstream>
#include <sstream>

#include "InputManager.hpp"

std::vector<Mesh> meshes;

HWND hwnd;

Size2 screenSize;

uint16_t fps;

uint32_t *pixels;

Camera camera;

float zFar = 1000;

void setZFar(float newZFar){
    zFar = newZFar;
}

uint16_t GetFps()
{
    return fps;
}

bool loadObject(const std::string &filename, std::vector<Triangle> &outTriangles)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    std::vector<Position3> vertices;
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v")
        {
            float x, y, z;
            ss >> x >> y >> z;
            vertices.push_back(Position3(x, y, z));
        }
        else if (prefix == "f")
        {
            int idx[3];
            for (int i = 0; i < 3; i++)
            {
                std::string vert;
                ss >> vert;
                size_t slash = vert.find('/');
                if (slash != std::string::npos)
                    vert = vert.substr(0, slash);
                idx[i] = std::stoi(vert) - 1;
            }
            outTriangles.push_back(Triangle(
                vertices[idx[0]],
                vertices[idx[1]],
                vertices[idx[2]]));
        }
    }

    return true;
}

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
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void DrawFilledTriangle(const Position2 &p0, const Position2 &p1, const Position2 &p2, int color)
{
    const Position2 *pts[3] = {&p0, &p1, &p2};
    if (pts[1]->y < pts[0]->y)
        std::swap(pts[0], pts[1]);
    if (pts[2]->y < pts[0]->y)
        std::swap(pts[0], pts[2]);
    if (pts[2]->y < pts[1]->y)
        std::swap(pts[1], pts[2]);

    auto drawScanline = [&](float y, float xStart, float xEnd)
    {
        int iy = static_cast<int>(y);
        if (iy < 0 || iy >= screenSize.h)
            return;

        if (xStart > xEnd)
            std::swap(xStart, xEnd);
        int ixStart = std::max(0, static_cast<int>(std::ceil(xStart)));
        int ixEnd = std::min(screenSize.w - 1, static_cast<int>(std::floor(xEnd)));

        for (int ix = ixStart; ix <= ixEnd; ix++)
            pixels[iy * screenSize.w + ix] = color;
    };

    auto interpolateX = [](float y, const Position2 &a, const Position2 &b) -> float
    {
        if (b.y - a.y == 0.0f)
            return a.x;
        return a.x + (b.x - a.x) * ((y - a.y) / (b.y - a.y));
    };

    for (float y = std::ceil(pts[0]->y); y <= std::floor(pts[1]->y); y++)
    {
        float xStart = interpolateX(y, *pts[0], *pts[2]);
        float xEnd = interpolateX(y, *pts[0], *pts[1]);
        drawScanline(y, xStart, xEnd);
    }

    for (float y = std::ceil(pts[1]->y); y <= std::floor(pts[2]->y); y++)
    {
        float xStart = interpolateX(y, *pts[0], *pts[2]);
        float xEnd = interpolateX(y, *pts[1], *pts[2]);
        drawScanline(y, xStart, xEnd);
    }
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
        if (msg.message == WM_QUIT)
        {
            free(pixels);
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    InvalidateRect(hwnd, nullptr, FALSE);

    count++;
    if (GetTickCount() - start >= 1000)
    {
        start = GetTickCount();
        fps = count;
        count = 0;
    }

    refreshInput();
    camera.updateState();

    SetCursor(cursor);
    return true;
}

void Init(int windowWidth, int windowHeight)
{
    screenSize.w = windowWidth;
    screenSize.h = windowHeight;

    pixels = (uint32_t *)malloc(screenSize.w * screenSize.h * sizeof(uint32_t));

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

void AddMesh(std::string fileName, Position3 position, uint32_t color)
{
    std::vector<Triangle> tris;
    if (!loadObject(fileName, tris))
    {
        std::cerr << "Failed to load model: " << fileName << std::endl;
    }

    Mesh mesh(tris, position, color, fileName);

    meshes.push_back(mesh);
}

void ScaleMesh(uint32_t index, float scale)
{
    for (Triangle &tri : meshes[index].tris)
    {
        for (Position3 &vertice : tri.vertices)
        {
            vertice.x *= scale;
            vertice.y *= scale;
            vertice.z *= scale;
        }
    }
}

void ScaleMesh(std::string name, float scale)
{
    int i = 0;
    for (Mesh mesh : meshes)
    {
        if (mesh.name == name)
        {
            ScaleMesh(i, scale);
            return;
        }
        i++;
    }

    std::cerr << "Couldn't find mesh: " << name << std::endl;
}

void MoveMesh(uint32_t index, Position3 delta)
{
    for (Triangle &tri : meshes[index].tris)
    {
        for (Position3 &vertice : tri.vertices)
        {
            vertice.x += delta.x;
            vertice.y += delta.y;
            vertice.z += delta.z;
        }
    }
}

void MoveMesh(std::string name, Position3 delta)
{
    int i = 0;
    for (Mesh mesh : meshes)
    {
        if (mesh.name == name)
        {
            MoveMesh(i, delta);
            return;
        }
        i++;
    }

    std::cerr << "Couldn't find mesh: " << name << std::endl;
}

void convertTriToView(Triangle tri, Camera camera, Position3 position, Vec4 out[3])
{
    for (int i = 0; i < 3; i++)
    {
        Position3 p = {tri.vertices[i].x + position.x - camera.x(),
                       tri.vertices[i].y + position.y - camera.y(),
                       tri.vertices[i].z + position.z - camera.z()};

        out[i].x = p.x * camera.getRight().x + p.y * camera.getRight().y + p.z * camera.getRight().z;
        out[i].y = p.x * camera.getUp().x + p.y * camera.getUp().y + p.z * camera.getUp().z;
        out[i].z = p.x * camera.getForward().x + p.y * camera.getForward().y + p.z * camera.getForward().z;
        out[i].w = 1;
    }
}

bool isTriInView(Vec4 viewP[3])
{
    for (int i = 0; i < 3; i++)
    {
        if (viewP[i].z <= 0)
        {
            return false;
        }
    }

    return true;
}

void convertViewToClip(Vec4 viewP[3], Vec4 out[3])
{
    float aspectRatio = (float)screenSize.w / (float)screenSize.h;
    float f = 1.0f / tanf(fov * 0.5f * (PI / 180.0f));
    for (int i = 0; i < 3; i++)
    {
        out[i].x = viewP[i].x * f / aspectRatio;
        out[i].y = viewP[i].y * f;
        out[i].z = viewP[i].z * (zFar + zNear) / (zNear - zFar) + (2 * zFar * zNear) / (zNear - zFar);
        out[i].w = -viewP[i].z;
    }
}

void convertClipToNormalized(Vec4 clipP[3], Position3 out[3])
{
    for (int i = 0; i < 3; i++)
    {
        out[i].x = clipP[i].x / clipP[i].w;
        out[i].y = clipP[i].y / clipP[i].w;
        out[i].z = clipP[i].z / clipP[i].w;
    }
}

void convertNormalizedToScreen(Position3 normalizedP[3], Position2 out[3])
{
    for (int i = 0; i < 3; i++)
    {
        out[i].x = ((normalizedP[i].x + 1) / 2) * screenSize.w;
        out[i].y = (1 - (normalizedP[i].y + 1) / 2) * screenSize.h;
    }
}

void DrawMeshes()
{
    for (Mesh mesh : meshes)
    {
        for (Triangle tri : mesh.tris)
        {
            Vec4 viewP[3];
            convertTriToView(tri, camera, mesh.position, viewP);

            if (!isTriInView(viewP))
            {
                continue;
            }

            Vec4 clipP[3];
            convertViewToClip(viewP, clipP);

            Position3 normalizedP[3];
            convertClipToNormalized(clipP, normalizedP);

            Position2 screenP[3];
            convertNormalizedToScreen(normalizedP, screenP);

            DrawFilledTriangle(screenP[0], screenP[1], screenP[2], mesh.color);
        }
    }
}