#pragma once
#include "Polygon.h"
class Triangle :
    public Polygon
{
public:
    Triangle();
    Triangle(const std::vector<Point>& arr);
    Triangle(const Triangle& other);
    const Triangle& operator = (const Triangle& other);
    virtual double Area();
};
