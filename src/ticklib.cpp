// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "ticklib.hpp"

#include <iostream>

#undef max
#undef min

#include <algorithm>
#include <fstream>
#include <sstream>

#include "Mesh.hpp"
#include "Camera.hpp"

#define PI 3.1415927f

struct Size2
{
    int w;
    int h;

    Size2() : w(0), h(0) {}
    Size2(int newW, int newH) : w(newW), h(newH) {}
};

std::vector<Mesh> meshes;

HWND hwnd;

Size2 screenSize;

uint16_t fps;

uint32_t *pixels;

Camera camera;

DWORD start = 0;
HCURSOR cursor;

uint8_t fov = 60;

struct Vec4
{
    float x;
    float y;
    float z;
    float w;

    Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4(float newX, float newY, float newZ, float newW) : x(newX), y(newY), z(newZ), w(newW) {}
};

std::vector<float> depthBuffer;

void tlSetFov(int newFov)
{
    if (newFov > 0 && newFov < 180)
    {
        fov = newFov;
    }
}

void tlSetCameraSpeed(float newSpeed)
{
    camera.setSpeed(newSpeed);
}

uint16_t tlGetFps()
{
    return fps;
}

bool loadObject(const std::string &fileName, std::vector<Triangle> &out, tlColor color)
{
    std::ifstream file(fileName);
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
            int indices[3];
            for (int i = 0; i < 3; i++)
            {
                std::string vert;
                ss >> vert;
                size_t slash = vert.find('/');
                if (slash != std::string::npos)
                {
                    vert = vert.substr(0, slash);
                }
                indices[i] = std::stoi(vert) - 1;
            }
            out.push_back(Triangle(
                vertices[indices[0]],
                vertices[indices[1]],
                vertices[indices[2]],
                color));
        }
    }

    return true;
}

void DrawLine(int x1, int y1, int x2, int y2, tlColor color, float z1, float z2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    int length = std::max(dx, dy);
    if (length == 0)
        length = 1;
    int step = 0;

    while (true)
    {
        if (x1 >= 0 && x1 < screenSize.w && y1 >= 0 && y1 < screenSize.h)
        {
            int idx = y1 * screenSize.w + x1;
            float t = (float)step / (float)length;
            float depth = z1 + t * (z2 - z1);
            if (depth < depthBuffer[idx])
            {
                depthBuffer[idx] = depth;
                pixels[idx] = color;
            }
        }

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
        step++;
    }
}

void DrawUnfilledTriangle(const Position2 &p0, const Position2 &p1, const Position2 &p2, tlColor color, float z0, float z1, float z2)
{
    DrawLine((int)std::round(p0.x), (int)std::round(p0.y), (int)std::round(p1.x), (int)std::round(p1.y), color, z0, z1);
    DrawLine((int)std::round(p1.x), (int)std::round(p1.y), (int)std::round(p2.x), (int)std::round(p2.y), color, z1, z2);
    DrawLine((int)std::round(p2.x), (int)std::round(p2.y), (int)std::round(p0.x), (int)std::round(p0.y), color, z2, z0);
}

void DrawFilledTriangle(const Position2 &p0, const Position2 &p1, const Position2 &p2, tlColor color, float z0, float z1, float z2)
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
        {
            float iz0 = 1.0f / z0;
            float iz1 = 1.0f / z1;
            float iz2 = 1.0f / z2;

            float depthA = iz0 + (iz2 - iz0) * ((y - pts[0]->y) / (pts[2]->y - pts[0]->y));
            float depthB = iz0 + (iz1 - iz0) * ((y - pts[0]->y) / (pts[1]->y - pts[0]->y));
            float t = (float)(ix - xStart) / (xEnd - xStart + 0.0001f);
            float iz = depthA + t * (depthB - depthA);
            float depth = 1.0f / iz;

            int idx = iy * screenSize.w + ix;
            if (depth < depthBuffer[idx])
            {
                depthBuffer[idx] = depth;
                pixels[idx] = color;
            }
        }
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

void tlClearBackground(tlColor color)
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

void tlInit(int windowWidth, int windowHeight)
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

    tlClearBackground(TlColors::Black);
    cursor = LoadCursor(nullptr, IDC_ARROW);
    start = GetTickCount();

    depthBuffer.resize(windowWidth * windowHeight);
}

void refreshInput();

bool tlWindowOpen()
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

    static int count = 0;
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

    for (auto &d : depthBuffer)
        d = FLT_MAX;

    return true;
}

std::string getFileName(const std::string &fullPath)
{
    size_t pos = fullPath.find_last_of("/\\");
    if (pos == std::string::npos)
        return fullPath;
    return fullPath.substr(pos + 1);
}

uint32_t tlAddMesh(std::string filePath, Position3 position, tlColor color)
{
    std::vector<Triangle> tris;
    if (!loadObject(filePath, tris, color))
    {
        std::cerr << "Failed to load model: " << filePath << std::endl;
    }

    std::cout << getFileName(filePath) << std::endl;
    Mesh mesh(tris, position, getFileName(filePath));

    meshes.push_back(mesh);
    return static_cast<uint32_t>(meshes.size() - 1);
}

void convertTriToView(Triangle tri, Camera camera, Position3 meshPosition, Vec4 out[3])
{
    for (int i = 0; i < 3; i++)
    {
        Position3 p = {tri.vertices[i].x + meshPosition.x - camera.x(),
                       tri.vertices[i].y + meshPosition.y - camera.y(),
                       tri.vertices[i].z + meshPosition.z - camera.z()};

        out[i].x = p.x * camera.getRight().x + p.y * camera.getRight().y + p.z * camera.getRight().z;
        out[i].y = p.x * camera.getUp().x + p.y * camera.getUp().y + p.z * camera.getUp().z;
        out[i].z = p.x * camera.getForward().x + p.y * camera.getForward().y + p.z * camera.getForward().z;
        out[i].w = 1;
    }
}

bool isTriangleInView(Vec4 viewP[3])
{
    for (int i = 0; i < 3; i++)
    {
        if (viewP[i].z <= 0.01f)
            return false;

        if (std::isnan(viewP[i].x) || std::isnan(viewP[i].y) || std::isnan(viewP[i].z) || std::isinf(viewP[i].x) || std::isinf(viewP[i].y) || std::isinf(viewP[i].z))
            return false;
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
        out[i].z = viewP[i].z;
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

void tlDrawMeshes(bool trianglesFilled)
{
    for (const Mesh &mesh : meshes)
    {
        for (const Triangle &tri : mesh.tris)
        {
            Vec4 viewP[3];
            convertTriToView(tri, camera, mesh.position, viewP);

            if (!isTriangleInView(viewP))
            {
                continue;
            }

            Vec4 clipP[3];
            convertViewToClip(viewP, clipP);

            Position3 normalizedP[3];
            convertClipToNormalized(clipP, normalizedP);

            Position2 screenP[3];
            convertNormalizedToScreen(normalizedP, screenP);

            if (trianglesFilled)
            {
                DrawFilledTriangle(screenP[0], screenP[1], screenP[2], tri.color, viewP[0].z, viewP[1].z, viewP[2].z);
            }
            else
            {
                DrawUnfilledTriangle(screenP[0], screenP[1], screenP[2], tri.color, viewP[0].z, viewP[1].z, viewP[2].z);
            }
        }
    }
}

void tlMoveMesh(uint32_t index, Position3 deltaPos) { MoveMesh(index, deltaPos); }
void tlMoveMesh(std::string name, Position3 deltaPos) { MoveMesh(name, deltaPos); }

void tlRotateMesh(uint32_t index, Rotation3 deltaRot) { RotateMesh(index, deltaRot); }
void tlRotateMesh(std::string name, Rotation3 deltaRot) { RotateMesh(name, deltaRot); }

void tlScaleMesh(uint32_t index, Scale3 deltaScale) { ScaleMesh(index, deltaScale); }
void tlScaleMesh(std::string name, Scale3 deltaScale) { ScaleMesh(name, deltaScale); }
void tlScaleMesh(uint32_t index, float deltaUniformScale) { ScaleMesh(index, deltaUniformScale); }
void tlScaleMesh(std::string name, float deltaUniformScale) { ScaleMesh(name, deltaUniformScale); }