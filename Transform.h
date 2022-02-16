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

    void SetRotationAngles(double x, double y, double z)
    {
        rotation = Quaternion::ToQuaternion(z, y, x);

        up -= position;
        forward -= position;
        right -= position;

        // Rotation along forward axis rotates up and right
        if(z != 0)
        {
            up = Quaternion::RotateVector(up, z, WorldSpace::forward);
            right = Quaternion::RotateVector(right, z, WorldSpace::forward);
        }
        

        // Rotation along up axis rotates forward and right
        if(y != 0)
        {
            forward = Quaternion::RotateVector(forward, y, WorldSpace::up);
            right = Quaternion::RotateVector(right, y, WorldSpace::up);
        }
       
        // Rotation along right axis rotates up and forward
        if(x != 0)
        {
            up = Quaternion::RotateVector(up, x, WorldSpace::right);
            forward = Quaternion::RotateVector(forward, x, WorldSpace::right);
        }

        up += position;
        forward += position;
        right += position;
    }

    
};