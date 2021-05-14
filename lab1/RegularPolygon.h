#pragma once
#include "Polygon.h"
class RegularPolygon :
    public Polygon
{
public:
    RegularPolygon();
    RegularPolygon(const std::vector<Point>& arr);
    RegularPolygon(const RegularPolygon& other);
    const RegularPolygon& operator=(const RegularPolygon& other);
};

