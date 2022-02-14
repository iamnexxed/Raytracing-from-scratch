#pragma once

#include <math.h>

struct Vector2Int
{
    int x;
    int y;
    // default constructor
    Vector2Int()
    {
        x = 0;
        y = 0;
    }

    Vector2Int(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    // overload + operator
    Vector2Int operator+(const Vector2Int &v)
    {
        Vector2Int result;
        result.x = x + v.x;
        result.y = y + v.y;
        return result;
    }
};

struct Vector2
{
    double x;
    double y;
    // default constructor
    Vector2()
    {
        x = 0;
        y = 0;
    }

    Vector2(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    // overload + operator
    Vector2 operator+(const Vector2 &v)
    {
        Vector2 result;
        result.x = this->x + v.x;
        result.y = this->y + v.y;
        return result;
    }
};

struct Vector3Int
{
    int x;
    int y;
    int z;
    // default constructor
    Vector3Int()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3Int(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    // overload + operator
    Vector3Int operator+(const Vector3Int &v)
    {
        Vector3Int result;
        result.x = x + v.x;
        result.y = y + v.y;
        result.z = z + v.z;
        return result;
    }
};

class Vector3
{
public:
    double x;
    double y;
    double z;
    // default constructor
    Vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    const static Vector3 zero;

    // overload + operator
    Vector3 operator+(const Vector3 &v)
    {
        Vector3 result;
        result.x = this->x + v.x;
        result.y = this->y + v.y;
        result.z = this->z + v.z;
        return result;
    }

    // overload - operator
    Vector3 operator-(const Vector3 &v)
    {
        Vector3 result;
        result.x = this->x - v.x;
        result.y = this->y - v.y;
        result.z = this->z - v.z;
        return result;
    }

    Vector3 operator-()
    {
        Vector3 result;
        result.x = -this->x;
        result.y = -this->y;
        result.z = -this->z;
        return result;
    }

    double Magnitude()
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3 operator*(double value)
    {
        Vector3 result;
        result.x = x * value;
        result.y = y * value;
        result.z = z * value;
        return result;
    }

    void Normalize()
    {
        double mag = Magnitude();
        if (mag > 0)
        {
            x /= mag;
            y /= mag;
            z /= mag;
        }
    }

    Vector3 Normalized()
    {
        double mag = Magnitude();
        Vector3 dir = Vector3::zero;
        if (mag > 0)
        {
            dir.x /= mag;
            dir.y /= mag;
            dir.z /= mag;
        }
        return dir;
    }

    

    static void SetVector(Vector3 &originalVec, Vector3 newVec)
    {
        originalVec = newVec;
    }

    static double DotProduct(Vector3 a, Vector3 b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static Vector3 CrossProduct(Vector3 a, Vector3 b)
    {
        return Vector3((a.y * b.z) - (a.x * b.z), -((a.x * b.z) - (a.z * b.x)), (a.x * b.y) - (a.y * b.x));
    }

    static Vector3 RotateVectorAround(Vector3 vector, Vector3 axis, double angle)
    {
        // Rodrigues rotation: https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
        return vector * std::cos(angle) + CrossProduct(axis, vector) * std::sin(angle) + axis * (1 - std::cos(angle)) * DotProduct(axis, vector);

    }
};



// 1 Unit Distance away
namespace WorldSpace
{
    const Vector3 up        ( 0,  1,  0);
    const Vector3 down      ( 0, -1,  0);
    const Vector3 left      (-1,  0,  0);
    const Vector3 right     ( 1,  0,  0);
    const Vector3 forward   ( 0,  0,  1);
    const Vector3 backward  ( 0,  0, -1);
}