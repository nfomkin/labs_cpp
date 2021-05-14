#pragma once
#include <iostream>
#include <vector>
#include "Point.h"


class Polyline
{
protected:
	std::vector<Point> arr;
public:
	Polyline();
	Polyline(const std::vector<Point>& arr);
	Polyline(const Polyline& other);
	const Polyline& operator = (const Polyline& other);
	void PrintCoordinates() const;
	void AddCoordinate(int x, int y);
	virtual double Length() const;
};

