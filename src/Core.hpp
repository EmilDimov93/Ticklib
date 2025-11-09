#pragma once

#include <functional>
#include <string>

#include "colors.h"

struct Position
{
    int x;
    int y;

    Position() : x(0), y(0) {}
    Position(int newX, int newY) : x(newX), y(newY) {}
};

struct Size
{
    int w;
    int h;

    Size() : w(0), h(0) {}
    Size(int newW, int newH) : w(newW), h(newH) {}
};

struct Button
{
    Position position;
    Size size;

    float roundness;
    float paddingRoundness;

    unsigned int backgroundColor;
    unsigned int paddingColor;
    unsigned int textColor;

    float padding;
    std::string text;

    std::function<void()> onClick;

    Button(
        const Position &newPosition,
        const Size &newSize,
        const std::string &newText,
        unsigned int newBackgroundColor,
        unsigned int newPaddingColor,
        unsigned int newTextColor,
        float newPadding = 4.0f,
        float newRoundness = 0.0f,
        float newPaddingRoundness = 0.0f,
        std::function<void()> newOnClick = nullptr)
    {
        position = newPosition;
        size = newSize;

        roundness = newRoundness;
        paddingRoundness = newPaddingRoundness;

        backgroundColor = newBackgroundColor;
        paddingColor = newPaddingColor;
        textColor = newTextColor;

        padding = newPadding;
        text = newText;

        onClick = newOnClick;
    }
};

void Init();

bool WindowOpen();

void ClearBackground();

void DrawRectangle(int x, int y, int w, int h, int color, float roundness = 0);

void DrawRectangle(Position position, Size size, int color, float roundness = 0);

void DrawButton(Button button);