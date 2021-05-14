#pragma once
#include "Polyline.h"
class ClosedPolyline :
    public Polyline
{
public:
    ClosedPolyline();
    ClosedPolyline(const std::vector<Point>& arr);
    ClosedPolyline(const ClosedPolyline& other);
    const ClosedPolyline& operator=(const ClosedPolyline& other);
    void PrintCoordinates() const;
    virtual double Length() const;
    const std::vector<Point>& GetArr() const;
};

