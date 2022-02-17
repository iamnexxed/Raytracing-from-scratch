#pragma once
#include "Transform.h"

double camera_rotation[3][3] = {0.7071, -0.7071, 0,
                                0.7071, 0.7071, 0,
                                0, 0, 1};

class Camera
{
public:
    Transform transform;
};