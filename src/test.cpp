#include "Core.hpp"
#include <iostream>

int main()
{
    Init();

    Button myButton(
        {100, 100},
        {200, 50},
        "Click Me",
        0xFF4444FF,
        0x222222FF,
        0xFFFFFFFF,
        5.0f,
        8.0f,
        4.0f,
        []() {
            std::cout << "Button clicked!\n";
        }
    );

    while (WindowOpen())
    {
        ClearBackground();
        DrawRectangle(Position(100, 100), Size(100, 100), COLOR_RED, 0.5f);
    }
}