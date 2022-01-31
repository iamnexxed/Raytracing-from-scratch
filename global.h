#pragma once

#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>

// canvas properties
#define CANVAS_WIDTH  600
#define CANVAS_HEIGHT 600
const int halfWindowWidth = CANVAS_WIDTH / 2;
const int halfWindowHeight = CANVAS_HEIGHT / 2;

// View port properties
#define VIEWPORT_WIDTH  600
#define VIEWPORT_HEIGHT 600
const double distanceToViewport = 600;

//const double INFINITY = 1e8;


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
    Vector2Int operator+(const Vector2Int& v)
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
    Vector2 operator+(const Vector2& v)
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
    Vector3Int operator+(const Vector3Int& v)
    {
        Vector3Int result;
        result.x = x + v.x;
        result.y = y + v.y;
        result.z = z + v.z;
        return result;
    }
};

struct Vector3
{
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

    // overload + operator
    Vector3 operator+(const Vector3& v)
    {
        Vector3 result;
        result.x = this->x + v.x;
        result.y = this->y + v.y;
        result.z = this->z + v.z;
        return result;
    }

    // overload - operator
    Vector3 operator-(const Vector3& v)
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
        if(mag > 0)
        {
            x = x / mag;
            y = y / mag;
            z = z / mag;
        }
           
    }
};

const Vector3 BLACK(0, 0, 0);

struct Sphere
{
    Vector3 center;
    double radius;
    Vector3 color;
    double specular;
    Sphere()
    {
        center = Vector3(0, 0, 0);
        radius = 0;
        color = Vector3(0, 0, 0);
        specular = -1;
    }

    // constructor
    Sphere(Vector3 center, double radius, Vector3 color)
    {
        this->center = center;
        this->radius = radius;
        this->color = color;
    }
};

// Convert from canvas coordinates to viewport coordinates.
Vector3 CanvasToViewport(Vector2Int &canvasCoord)
{
    Vector3 viewport;
    viewport.x = canvasCoord.x * VIEWPORT_WIDTH / CANVAS_WIDTH;
    viewport.y = canvasCoord.y * VIEWPORT_HEIGHT / CANVAS_HEIGHT;
    viewport.z = distanceToViewport;
    return viewport;
}

double DotProduct(Vector3 a, Vector3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}


// get a point on the ray
Vector3 PointOnRay(Vector3 rayOrigin, Vector3 rayDirection, double t)
{
    Vector3 pointOnRay;
    pointOnRay.x = rayOrigin.x + rayDirection.x * t;
    pointOnRay.y = rayOrigin.y + rayDirection.y * t;
    pointOnRay.z = rayOrigin.z + rayDirection.z * t;
    return pointOnRay;
}
