#pragma once
#include <ciso646>
#include "ClosedPolyline.h"

class Polygon
{
protected:
	ClosedPolyline border;
public:
	Polygon(const std::vector<Point>& arr);
	Polygon(const Polygon& other);
	Polygon();
	const Polygon& operator=(const Polygon& other);
	void PrintCoordinates() const;
	virtual double Perimetr() const;
	virtual double Area();
};

