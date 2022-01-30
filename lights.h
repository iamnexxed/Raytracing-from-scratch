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
    lightSources[1].intensity = 0.8;
    lightSources[1].position = Vector3(2, 1, 0);

    lightSources[2].type = Directional;
    lightSources[2].intensity = 0.8;
    lightSources[2].direction = Vector3(1, 4, 4);
}

double ComputeLighting(Vector3 point, Vector3 normal)
{
    double intensity = 0.0;
    Vector3 L(0, 0, 0);
    for(int i = 0; i < NUMOFLIGHTS; ++i)
    {
        if(lightSources[i].type == Ambient)
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
        if(nDotL > 0)
        {
            intensity += lightSources[i].intensity * nDotL / (normal.Magnitude() * L.Magnitude());
        }
    }
    return intensity;
}