#pragma once

#include "global.h"

enum LightType
{
    Ambient,
    Point,
    Directional
};

struct Light
{
    LightType type;
    double intensity;
    Vector3 position;
    Vector3 direction;
};

const int NUMOFLIGHTS = 3;

Light lightSources[NUMOFLIGHTS];

void LoadLightSources()
{
    lightSources[0].type = Ambient;
    lightSources[0].intensity = 0.2;
    lightSources[0].position = Vector3(0, 0, 0);

    lightSources[1].type = Point;
    lightSources[1].intensity = 0.5;
    lightSources[1].position = Vector3(2, 1, 0);

    lightSources[2].type = Directional;
    lightSources[2].intensity = 0.8;
    lightSources[2].direction = Vector3(0, 1, 0);
}

// Light Absorption
double ComputeLighting(Vector3 point, Vector3 normal)
{
    double intensity = 0.0;
    Vector3 L(0, 0, 0);
    for (int i = 0; i < NUMOFLIGHTS; ++i)
    {
        if (lightSources[i].type == Ambient)
        {
            intensity += lightSources[i].intensity;
        }
        else if (lightSources[i].type == Point)
        {
            L = lightSources[i].position - point;
        }
        else if (lightSources[i].type == Directional)
        {
            L = lightSources[i].direction;
        }
        double nDotL = DotProduct(normal, L);
        if (nDotL > 0)
        {
            intensity += lightSources[i].intensity * nDotL / (normal.Magnitude() * L.Magnitude());
        }
    }
    return intensity;
}

Vector2 IntersectRaySphere(Vector3 rayOrigin, Vector3 rayDirection, Sphere &sphere)
{
    Vector2 t(-INFINITY, -INFINITY);

    // (t2D, D) + t(2CO, D) + (CO, CO) − r2 = 0

    double a = DotProduct(rayDirection, rayDirection);

    double b = 2 * DotProduct(rayOrigin - sphere.center, rayDirection);

    double c = DotProduct(rayOrigin - sphere.center, rayOrigin - sphere.center) - sphere.radius * sphere.radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        t.x = (-b + sqrt(discriminant)) / (2 * a);
        t.y = (-b - sqrt(discriminant)) / (2 * a);
    }

    return t;
}

Sphere* ClosestSphereIntersection(Vector3 &origin, Vector3 &direction, double tMin, double tMax, Sphere *spheres, const int NUM_SPHERES, double &closestT)
{
    Sphere *closestSphere = nullptr;
    closestT = INFINITY;

    for (int i = 0; i < NUM_SPHERES; i++)
    {
        Vector2 t = IntersectRaySphere(origin, direction, spheres[i]);
        if (t.x >= tMin && t.x <= tMax && t.x < closestT)
        {
            closestT = t.x;
            closestSphere = &spheres[i];
        }

        if (t.y >= tMin && t.y <= tMax && t.y < closestT)
        {
            closestT = t.y;
            closestSphere = &spheres[i];
        }
    }

    return closestSphere;
}

// Absorption and reflection and shadows
double ComputeLighting(Vector3 point, Vector3 normal, Vector3 viewVector, double spec, Sphere *spheres, const int NUM_SPHERES)
{
    double intensity = 0.0;
    Vector3 L(0, 0, 0);

    double tMax = 0;

    for (int i = 0; i < NUMOFLIGHTS; ++i)
    {
        if (lightSources[i].type == Ambient)
        {
            intensity += lightSources[i].intensity;
        }
        else if (lightSources[i].type == Point)
        {
            L = lightSources[i].position - point;
            tMax = 1;
        }
        else if (lightSources[i].type == Directional)
        {
            L = lightSources[i].direction;
            tMax = INFINITY;
        }

        // Shadow check
        if (tMax > 0)
        {
            double shadowT = 0;
            Sphere *shadowSphere = ClosestSphereIntersection(point, L, 0.001, tMax, spheres, NUM_SPHERES, shadowT);
            
            
            if (shadowSphere != nullptr)
            {
                continue;
            }
        }

        double nDotL = DotProduct(normal, L);
        // Diffuse lighting
        if (nDotL > 0)
        {
            intensity += lightSources[i].intensity * nDotL / (normal.Magnitude() * L.Magnitude());
        }

        // Specular lighting
        if (spec > 0)
        {
            Vector3 R = normal * DotProduct(normal, L) * 2 - L;
            double rDotV = DotProduct(R, viewVector);
            if (rDotV > 0)
            {
                intensity += lightSources[i].intensity * std::pow(rDotV / (R.Magnitude() * viewVector.Magnitude()), spec);
            }
        }
    }
    return intensity;
}


Vector3 TraceRayOnSpheres(Vector3 rayOrigin, Vector3 rayDirection, double tMin, double tMax, Sphere *spheres, const int NUM_SPHERES)
{
    Vector3 color = BLACK;

    double closestT = tMax;

    Sphere *closestSphere = nullptr;

    for (int i = 0; i < NUM_SPHERES; i++)
    {
        Vector2 t = IntersectRaySphere(rayOrigin, rayDirection, spheres[i]);

        if (t.x >= tMin && t.x <= tMax && t.x < closestT)
        {
            closestT = t.x;
            closestSphere = &spheres[i];
        }

        if (t.y >= tMin && t.y <= tMax && t.y < closestT)
        {
            closestT = t.y;
            closestSphere = &spheres[i];
        }
    }

    if (closestSphere != nullptr)
    {

        Vector3 P = rayOrigin + rayDirection * closestT;
        Vector3 N = P - closestSphere->center;
        N.Normalize();

        color = closestSphere->color * ComputeLighting(P, N, -rayDirection, closestSphere->specular, spheres, NUM_SPHERES);

        // color = closestSphere->color * ComputeLighting(P, N);
        // color = closestSphere->color;
    }

    return color;
}

Vector3 TraceRayOnObjects(Vector3 rayOrigin, Vector3 rayDirection, double tMin, double tMax, Sphere *spheres, const int NUM_SPHERES)
{
    double closestT = 0;

    Sphere *closestSphere = ClosestSphereIntersection(rayOrigin, rayDirection, tMin, tMax, spheres, NUM_SPHERES, closestT);
    

    Vector3 color = BLACK;

    if (closestSphere != nullptr)
    {

        Vector3 P = rayOrigin + rayDirection * closestT;
        Vector3 N = P - closestSphere->center;
        N.Normalize();

        color = closestSphere->color * ComputeLighting(P, N, -rayDirection, closestSphere->specular, spheres, NUM_SPHERES);

        // color = closestSphere->color * ComputeLighting(P, N);
        // color = closestSphere->color;
    }

    return color;
}

