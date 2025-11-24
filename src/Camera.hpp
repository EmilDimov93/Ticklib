// Copyright 2025 Emil Dimov
// Licensed under the Apache License, Version 2.0

#include "definitions.hpp"
#include "InputManager.hpp"

class Camera{
private:
    Position3 position = {0, 0, -10};

    Rotation2 rotation = {0, 0};

    Position3 forward;
    Position3 right;
    Position3 up;

public:
    float x();
    float y();
    float z();

    Position3 getForward();
    Position3 getRight();
    Position3 getUp();

    void updateState();
};