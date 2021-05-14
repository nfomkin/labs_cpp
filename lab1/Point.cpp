#include "Point.h"

Point::Point() : x(0), y(0) {}

Point::Point(int x, int y) : x(x), y(y) {}

double Point::distance(const Point& a, const Point& b)
{
	int x, y;
	x = abs(a.x - b.x);
	y = abs(a.y - b.y);
	return sqrt(pow(x, 2) + pow(y, 2));
}
