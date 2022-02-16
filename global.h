#pragma once

#include <windows.h>
#include <gl/glut.h>
#include "Coordinate.h"
#include <stdio.h>
#include "Camera.h"

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


const Vector3 BLACK(0, 0, 0);



struct Sphere
{
    Vector3 center;
    double radius;
    Vector3 color;
    double specular;
    double reflectivity;
    Sphere()
    {
        center = Vector3(0, 0, 0);
        radius = 0;
        color = Vector3(0, 0, 0);
        specular = -1;
        reflectivity = 0;
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



// get a point on the ray
Vector3 PointOnRay(Vector3 rayOrigin, Vector3 rayDirection, double t)
{
    Vector3 pointOnRay;
    pointOnRay.x = rayOrigin.x + rayDirection.x * t;
    pointOnRay.y = rayOrigin.y + rayDirection.y * t;
    pointOnRay.z = rayOrigin.z + rayDirection.z * t;
    return pointOnRay;
}
