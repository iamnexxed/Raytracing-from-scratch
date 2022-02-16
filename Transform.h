#pragma once
#include "Coordinate.h"


class Transform
{
private:
    Vector3 forward;
    Vector3 up;
    Vector3 right;

    

public: 
    Vector3 position;
    Quaternion rotation;
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


    void SetRotationAngles(double xRad, double yRad, double zRad)
    {
        rotation = Quaternion::ToQuaternion(zRad, yRad, xRad);

        up -= position;
        forward -= position;
        right -= position;

        // Rotation along forward axis rotates up and right
        if (zRad != 0)
        {
            up = Quaternion::RotateVector(up, zRad, WorldSpace::forward);
            right = Quaternion::RotateVector(right, zRad, WorldSpace::forward);
        }
        

        // Rotation along up axis rotates forward and right
        if (yRad != 0)
        {
            forward = Quaternion::RotateVector(forward, yRad, WorldSpace::up);
            right = Quaternion::RotateVector(right, yRad, WorldSpace::up);
        }
       
        // Rotation along right axis rotates up and forward
        if (xRad != 0)
        {
            up = Quaternion::RotateVector(up, xRad, WorldSpace::right);
            forward = Quaternion::RotateVector(forward, xRad, WorldSpace::right);
        }

        up += position;
        forward += position;
        right += position;
    }

    
};