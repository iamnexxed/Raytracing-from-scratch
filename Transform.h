#pragma once
#include "Coordinate.h"


class Transform
{
private:
    Vector3 forward;
    Vector3 up;
    Vector3 right;

    Vector3 rotation;

public: 
    Vector3 position;
    Vector3 scale;


public:
    Transform()
    {
        Vector3::SetVector(forward, position + WorldSpace::forward);
        Vector3::SetVector(up, position + WorldSpace::up);
        Vector3::SetVector(right, position + WorldSpace::right);
    }

    Vector3 GetForward()
    {
        return forward;
    }
    Vector3 GetRight()
    {
        return right;
    }
    Vector3 GetUp()
    {
        return up;
    }

    void SetRotationAngles(double x, double y, double z)
    {
        rotation.x = x;
        rotation.y = y;
        rotation.z = z;

        //forward.x = ;//set direction values according to matrix operations
        
    }

    Vector3 GetAngles()
    {
        return rotation;
    }

   
    
};