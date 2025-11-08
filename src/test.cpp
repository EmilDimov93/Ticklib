#include "Core.hpp"
#include <iostream>

int main()
{
    Init();

    while (WindowOpen())
    {
        ClearBackground();
        DrawRectangle(Position(100, 100), Size(100, 100), COLOR_RED, 0.5f);
    }
}