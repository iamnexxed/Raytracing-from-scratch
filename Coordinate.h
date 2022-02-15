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

    static Vector3 RotateVectorAround(Vector3 vector, Vector3 axis, double angleRadians)
    {
        // Rodrigues rotation: https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
        return vector * std::cos(angleRadians) + CrossProduct(axis, vector) * std::sin(angleRadians) + axis * (1 - std::cos(angleRadians)) * DotProduct(axis, vector);
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

// Reference: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
class Quaternion
{
public:
    double real;
    Vector3 img;
    Quaternion()
    {
        real = 0;
        img = Vector3::zero;
    }

    Quaternion(Vector3 eulerAngles)
    {
        Quaternion q = ToQuaternion(eulerAngles);
        real = q.real;
        img = q.img;
    }

    Quaternion(double real, Vector3 img)
    {
        this->real = real;
        this->img = img;
    }

    // Arithmetic operations on Quaternions: https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/arithmetic/index.htm
    Quaternion operator*(const Quaternion& other)
    {
        Quaternion result;
        result.real = real * other.real - img.x * other.img.x - img.y * other.img.y - img.z * other.img.z;
        result.img.x = img.x * other.real + real * other.img.x + img.y * other.img.z - img.z * other.img.y;
        result.img.y = real * other.img.y - img.x * other.img.z + img.y * other.real + img.z * other.img.y;
        result.img.z = real * other.img.z + img.x * other.img.y - img.y * other.img.x + img.z * other.real;
        return result;

    }

    static Quaternion RotationAroundAxis(double angleRadians, Vector3 axis)
    {
        axis.Normalize();
        return Quaternion(std::cos(angleRadians * 0.5), axis * std::sin(angleRadians * 0.5));
    }


    static Vector3 RotateVector(Vector3 v, Quaternion q)
    {
        // v_new = v + (2 * q_img) x (q_img x v + (q_real * v))
        // * denotes scalar multiplication
        // x denotes cross product
        return v + Vector3::CrossProduct((q.img) * 2, (Vector3::CrossProduct(q.img, v) + v * q.real));
    }

    static Vector3 RotateVector(Vector3 v, double angleRadians, Vector3 axis)
    {
        return RotateVector(v, RotationAroundAxis(angleRadians, axis));
    }

    static Quaternion ToQuaternion(double yaw, double pitch, double roll) // yaw (Z), pitch (Y), roll (X)
    {
        Quaternion result;
        // Abbreviations for the various angular functions
        double cy = cos(yaw * 0.5);
        double sy = sin(yaw * 0.5);
        double cp = cos(pitch * 0.5);
        double sp = sin(pitch * 0.5);
        double cr = cos(roll * 0.5);
        double sr = sin(roll * 0.5);

        result.real = cr * cp * cy + sr * sp * sy;
        result.img.x = sr * cp * cy - cr * sp * sy;
        result.img.y = cr * sp * cy + sr * cp * sy;
        result.img.z = cr * cp * sy - sr * sp * cy;

        return result;
    }

    static Quaternion ToQuaternion(Vector3 eulerAngles)
    {
        return ToQuaternion(eulerAngles.z, eulerAngles.y, eulerAngles.x);
    }

    static Vector3 ToEulerAngles(Quaternion quaternion)
    {
        Vector3 eulerAngles;

        eulerAngles.x = std::atan2(2 * (quaternion.real * quaternion.img.x + quaternion.img.y * quaternion.img.z), 1 - 2 * (quaternion.img.x * quaternion.img.x + quaternion.img.y * quaternion.img.y));
        
        double sinp = 2 * (quaternion.real * quaternion.img.y - quaternion.img.z * quaternion.img.x);
        
        eulerAngles.y = std::abs(sinp) >= 1 ? std::copysign(M_PI * 0.5, sinp) : std::asin(sinp);

        eulerAngles.z = std::atan2(2 * (quaternion.real * quaternion.img.z + quaternion.img.x * quaternion.img.y), 1 - 2 * (quaternion.img.y * quaternion.img.y + quaternion.img.z * quaternion.img.z));

        return eulerAngles;
    }
};