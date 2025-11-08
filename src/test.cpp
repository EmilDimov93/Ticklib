#include "Core.hpp"
#include <iostream>
int main() {
    Init();

    bool a = true;
    int counter = 0;
    while(WindowOpen()){
        DrawRectangle(100, 100, 100, 100, COLOR_RED, 0.2f);
    }

    return 0;
}