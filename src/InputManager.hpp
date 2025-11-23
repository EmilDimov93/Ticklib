#pragma once

#include "definitions.hpp"
#include <windows.h>

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

class InputManager
{
public:
    InputManager();

    void refresh();

    bool isDown(TLMouseBtn key);
    bool isUp(TLMouseBtn key);
    bool isPressed(TLMouseBtn key);
    bool isReleased(TLMouseBtn key);

    bool isDown(TLKey key);
    bool isUp(TLKey key);
    bool isPressed(TLKey key);
    bool isReleased(TLKey key);

    Position2 getMousePos();

private:
    KeyState mouseBtnStates[TL_MOUSE_BTN_COUNT];
    KeyState keyStates[TL_KEY_COUNT];

    Position2 mousePosition;
};