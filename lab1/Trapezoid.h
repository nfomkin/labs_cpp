#pragma once
#include "Polygon.h"
class Trapezoid :
    public Polygon
{
public:
    Trapezoid();
    Trapezoid(const std::vector<Point>& arr);
    Trapezoid(const Trapezoid& other);
    const Trapezoid& operator = (const Trapezoid& other);
};

