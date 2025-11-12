#include "Core.hpp"
#include <iostream>

int main()
{
    Init();

    Button myButton(
        {400, 100},
        {100, 100},
        "Ex",
        COLOR_RED,
        COLOR_YELLOW,
        COLOR_BLUE,
        4.0f,
        0.3f,
        0.4f,
        []() {
            printf("Play Game button clicked!\n");
        });

    int x = 100;
    int y = 100;
    int z = 5;

    while (WindowOpen())
    {
        ClearBackground();
        DrawRectangle(Position(100 / 6, 100 / 6), Size(100, 100), COLOR_RED, 0.5f);
        //DrawButton(myButton);
    }
}