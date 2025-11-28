// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#pragma once

#include <string>
#include <windows.h>

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

#define TL_DEFAULT_CAMERA_SPEED 5.0f
#define TL_DEFAULT_FOV 60

void tlInit(int windowWidth, int windowHeight);

bool tlWindowOpen();

void tlClearBackground(uint32_t color);

uint16_t tlGetFps();

void tlAddMesh(std::string fileName, Position3 position, uint32_t color);

void tlDrawMeshes(bool trianglesFilled);

void tlSetCameraSpeed(float newSpeed);

void tlSetFov(int newFov);

void tlMoveMesh(uint32_t index, Position3 delta);
void tlMoveMesh(std::string name, Position3 delta);

void tlRotateMesh(uint32_t index, Rotation3 rotation);
void tlRotateMesh(std::string name, Rotation3 rotation);

void tlScaleMesh(uint32_t index, Scale3 scale);
void tlScaleMesh(std::string name, Scale3 scale);
void tlScaleMesh(uint32_t index, float scale);
void tlScaleMesh(std::string name, float scale);

typedef enum
{
    KEY_STATE_DOWN,
    KEY_STATE_UP,
    KEY_STATE_PRESSED,
    KEY_STATE_RELEASED
} KeyState;

#define TL_MOUSE_BTN_COUNT 5

typedef enum
{
    TL_MOUSE_BTN_LEFT = 0,
    TL_MOUSE_BTN_RIGHT,
    TL_MOUSE_BTN_MIDDLE,
    TL_MOUSE_BTN_X1,
    TL_MOUSE_BTN_X2
} TLMouseBtn;

#define TL_KEY_COUNT 256

typedef enum
{
    TL_KEY_A = 'A',
    TL_KEY_B = 'B',
    TL_KEY_C = 'C',
    TL_KEY_D = 'D',
    TL_KEY_E = 'E',
    TL_KEY_F = 'F',
    TL_KEY_G = 'G',
    TL_KEY_H = 'H',
    TL_KEY_I = 'I',
    TL_KEY_J = 'J',
    TL_KEY_K = 'K',
    TL_KEY_L = 'L',
    TL_KEY_M = 'M',
    TL_KEY_N = 'N',
    TL_KEY_O = 'O',
    TL_KEY_P = 'P',
    TL_KEY_Q = 'Q',
    TL_KEY_R = 'R',
    TL_KEY_S = 'S',
    TL_KEY_T = 'T',
    TL_KEY_U = 'U',
    TL_KEY_V = 'V',
    TL_KEY_W = 'W',
    TL_KEY_X = 'X',
    TL_KEY_Y = 'Y',
    TL_KEY_Z = 'Z',
    TL_KEY_0 = '0',
    TL_KEY_1 = '1',
    TL_KEY_2 = '2',
    TL_KEY_3 = '3',
    TL_KEY_4 = '4',
    TL_KEY_5 = '5',
    TL_KEY_6 = '6',
    TL_KEY_7 = '7',
    TL_KEY_8 = '8',
    TL_KEY_9 = '9',
    TL_KEY_F1 = VK_F1,
    TL_KEY_F2 = VK_F2,
    TL_KEY_F3 = VK_F3,
    TL_KEY_F4 = VK_F4,
    TL_KEY_F5 = VK_F5,
    TL_KEY_F6 = VK_F6,
    TL_KEY_F7 = VK_F7,
    TL_KEY_F8 = VK_F8,
    TL_KEY_F9 = VK_F9,
    TL_KEY_F10 = VK_F10,
    TL_KEY_F11 = VK_F11,
    TL_KEY_F12 = VK_F12,
    TL_KEY_SPACE = VK_SPACE,
    TL_KEY_ENTER = VK_RETURN,
    TL_KEY_ESCAPE = VK_ESCAPE,
    TL_KEY_TAB = VK_TAB,
    TL_KEY_BACKSPACE = VK_BACK,
    TL_KEY_INSERT = VK_INSERT,
    TL_KEY_DELETE = VK_DELETE,
    TL_KEY_RIGHT = VK_RIGHT,
    TL_KEY_LEFT = VK_LEFT,
    TL_KEY_UP = VK_UP,
    TL_KEY_DOWN = VK_DOWN,
    TL_KEY_HOME = VK_HOME,
    TL_KEY_END = VK_END,
    TL_KEY_PAGE_UP = VK_PRIOR,
    TL_KEY_PAGE_DOWN = VK_NEXT,
    TL_KEY_LEFT_SHIFT = VK_LSHIFT,
    TL_KEY_RIGHT_SHIFT = VK_RSHIFT,
    TL_KEY_LEFT_CONTROL = VK_LCONTROL,
    TL_KEY_RIGHT_CONTROL = VK_RCONTROL,
    TL_KEY_LEFT_ALT = VK_LMENU,
    TL_KEY_RIGHT_ALT = VK_RMENU
} TLKey;

void refreshInput();

bool tlIsDown(TLMouseBtn key);
bool tlIsUp(TLMouseBtn key);
bool tlIsPressed(TLMouseBtn key);
bool tlIsReleased(TLMouseBtn key);

bool tlIsDown(TLKey key);
bool tlIsUp(TLKey key);
bool tlIsPressed(TLKey key);
bool tlIsReleased(TLKey key);

Position2 tlGetMousePos();