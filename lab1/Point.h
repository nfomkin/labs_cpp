#pragma once
#include <cmath>

class Point
{
public:
	int x;
	int y;

	Point();
	Point(int x, int y);
	static double distance(const Point& a, const Point& b);
};

