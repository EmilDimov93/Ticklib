// Copyright 2025 Emil Dimov
// Licensed under the Apache License, TLrsion 2.0

#include "InputManager.hpp"
#include <windows.h>

InputManager::InputManager()
{
    for (size_t i = 0; i < TL_MOUSE_BTN_COUNT; i++)
        mouseBtnStates[i] = KEY_STATE_UP;

    for (size_t i = 0; i < TL_KEY_COUNT; i++)
        keyStates[i] = KEY_STATE_UP;

    mousePosition = {0, 0};
}

void InputManager::refresh()
{
    for (int i = 0; i < TL_KEY_COUNT; i++)
    {
        bool isKeyDown = (GetAsyncKeyState(i) & 0x8000) != 0;

        switch (keyStates[i])
        {
        case KEY_STATE_UP:
        case KEY_STATE_RELEASED:
            keyStates[i] = isKeyDown ? KEY_STATE_PRESSED : KEY_STATE_UP;
            break;
        case KEY_STATE_DOWN:
        case KEY_STATE_PRESSED:
            keyStates[i] = isKeyDown ? KEY_STATE_DOWN : KEY_STATE_RELEASED;
            break;
        }
    }

    int mouseButtons[TL_MOUSE_BTN_COUNT] = {VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2};
    for (int i = 0; i < TL_MOUSE_BTN_COUNT; i++)
    {
        bool isBtnDown = (GetAsyncKeyState(mouseButtons[i]) & 0x8000) != 0;

        switch (mouseBtnStates[i])
        {
        case KEY_STATE_UP:
        case KEY_STATE_RELEASED:
            mouseBtnStates[i] = isBtnDown ? KEY_STATE_PRESSED : KEY_STATE_UP;
            break;
        case KEY_STATE_DOWN:
        case KEY_STATE_PRESSED:
            mouseBtnStates[i] = isBtnDown ? KEY_STATE_DOWN : KEY_STATE_RELEASED;
            break;
        }
    }

    POINT p;
    if (GetCursorPos(&p))
    {
        mousePosition.x = (float)p.x;
        mousePosition.y = (float)p.y;
    }
}

bool InputManager::isDown(TLMouseBtn btn)
{
    if (btn >= TL_MOUSE_BTN_COUNT) return false;
    return mouseBtnStates[btn] == KEY_STATE_DOWN || mouseBtnStates[btn] == KEY_STATE_PRESSED;
}

bool InputManager::isUp(TLMouseBtn btn)
{
    if (btn >= TL_MOUSE_BTN_COUNT) return false;
    return mouseBtnStates[btn] == KEY_STATE_UP || mouseBtnStates[btn] == KEY_STATE_RELEASED;
}

bool InputManager::isPressed(TLMouseBtn btn)
{
    if (btn >= TL_MOUSE_BTN_COUNT) return false;
    return mouseBtnStates[btn] == KEY_STATE_PRESSED;
}

bool InputManager::isReleased(TLMouseBtn btn)
{
    if (btn >= TL_MOUSE_BTN_COUNT) return false;
    return mouseBtnStates[btn] == KEY_STATE_RELEASED;
}

bool InputManager::isDown(TLKey key)
{
    if (key >= TL_KEY_COUNT) return false;
    return keyStates[key] == KEY_STATE_DOWN || keyStates[key] == KEY_STATE_PRESSED;
}

bool InputManager::isUp(TLKey key)
{
    if (key >= TL_KEY_COUNT) return false;
    return keyStates[key] == KEY_STATE_UP || keyStates[key] == KEY_STATE_RELEASED;
}

bool InputManager::isPressed(TLKey key)
{
    if (key >= TL_KEY_COUNT) return false;
    return keyStates[key] == KEY_STATE_PRESSED;
}

bool InputManager::isReleased(TLKey key)
{
    if (key >= TL_KEY_COUNT) return false;
    return keyStates[key] == KEY_STATE_RELEASED;
}

Position2 InputManager::getMousePos()
{
    return mousePosition;
}