// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#pragma once

#include <string>
#include <windows.h>

// Color type for clarity
using tlColor = uint32_t;

// RGBA colors in format 0xAARRGGBB
struct TlColors
{
    static constexpr tlColor White = 0xFFFFFFFF;
    static constexpr tlColor Black = 0xFF000000;
    static constexpr tlColor Red = 0xFFFF0000;
    static constexpr tlColor Green = 0xFF00FF00;
    static constexpr tlColor Blue = 0xFF0000FF;
    static constexpr tlColor Yellow = 0xFFFFFF00;
    static constexpr tlColor Cyan = 0xFF00FFFF;
    static constexpr tlColor Magenta = 0xFFFF00FF;
    static constexpr tlColor Orange = 0xFFFFA500;
    static constexpr tlColor Purple = 0xFF800080;
    static constexpr tlColor Pink = 0xFFFF69B4;
    static constexpr tlColor Brown = 0xFF8B4513;
    static constexpr tlColor Gray = 0xFF808080;
    static constexpr tlColor LightGray = 0xFFD3D3D3;
    static constexpr tlColor DarkGray = 0xFF404040;
    static constexpr tlColor LightBlue = 0xFFA0C8FF;
};

// Mouse buttons. Used with input functions
typedef enum
{
    TL_MOUSE_BTN_LEFT = 0,
    TL_MOUSE_BTN_RIGHT,
    TL_MOUSE_BTN_MIDDLE,
    TL_MOUSE_BTN_X1,
    TL_MOUSE_BTN_X2
} TLMouseBtn;

// Keyboard keys. Used with input functions
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

// Separate structures for clarity

// 2D coordinate
struct Position2
{
    float x, y;

    Position2() : x(0), y(0) {}
    Position2(float newX, float newY) : x(newX), y(newY) {}
};

// 3D coordinate
struct Position3
{
    float x, y, z;

    Position3() : x(0), y(0), z(0) {}
    Position3(float newX, float newY, float newZ) : x(newX), y(newY), z(newZ) {}
};

// 3D scale
struct Scale3
{
    float x, y, z;

    Scale3() : x(0), y(0), z(0) {}
    Scale3(float newX, float newY, float newZ) : x(newX), y(newY), z(newZ) {}
};

// 3D rotation in degrees
struct Rotation3
{
    float pitch, yaw, roll;

    Rotation3() : pitch(0), yaw(0), roll(0) {}
    Rotation3(float newPitch, float newYaw, float newRoll) : pitch(newPitch), yaw(newYaw), roll(newRoll) {}
};

// Initializes Ticklib and creates a window
void tlInit(int windowWidth, int windowHeight);

// Returns true while the window is open
bool tlWindowOpen();

// Clears the screen with the given RGBA color
void tlClearBackground(tlColor color);

// Returns the current Frames Per Second
uint16_t tlGetFps();

// Loads triangulated .obj file and adds it to the list of meshes
uint32_t tlAddMesh(std::string filePath, Position3 position, tlColor color);

// Draws all added meshes. If the argument is true, triangles are filled, otherwise meshes are drawn as wireframes
void tlDrawMeshes(bool trianglesFilled);

// Sets camera movement speed. Default is 5.0f
void tlSetCameraSpeed(float newSpeed);

// Sets Field Of View. Default is 60 degrees
void tlSetFov(int newFov);

// Mesh manipulation functions have overloads to allow for searching by filename

// Moves mesh by given delta
void tlMoveMesh(uint32_t index, Position3 deltaPos);
void tlMoveMesh(std::string name, Position3 deltaPos);

// Rotates mesh
void tlRotateMesh(uint32_t index, Rotation3 deltaRot);
void tlRotateMesh(std::string name, Rotation3 deltaRot);

// Scales mesh. Also has uniform overload
void tlScaleMesh(uint32_t index, Scale3 deltaScale);
void tlScaleMesh(std::string name, Scale3 deltaScale);
void tlScaleMesh(uint32_t index, float deltaUniformScale);
void tlScaleMesh(std::string name, float deltaUniformScale);

// Returns true if mouse button / keyboard key is down
bool tlIsDown(TLMouseBtn btn);
bool tlIsDown(TLKey key);

// Returns true if mouse button / keyboard key is up
bool tlIsUp(TLMouseBtn btn);
bool tlIsUp(TLKey key);

// Returns true on the first frame a mouse button / keyboard key is pressed
bool tlIsPressed(TLMouseBtn btn);
bool tlIsPressed(TLKey key);

// Returns true on the first frame a mouse button / keyboard key is released
bool tlIsReleased(TLMouseBtn btn);
bool tlIsReleased(TLKey key);

// Returns the current mouse cursor position
Position2 tlGetMousePos();