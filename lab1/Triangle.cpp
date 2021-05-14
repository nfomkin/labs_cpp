#include "Triangle.h"

Triangle::Triangle() : Polygon() {}

Triangle::Triangle(const std::vector<Point>& arr) : Polygon(arr)
{
	if (border.GetArr().size() != 3)
	{
		throw std::exception("The triangle must consist of 3 points");
	}
}

Triangle::Triangle(const Triangle& other) : border(other.border)
{
	//border.GetArr() = other.border.GetArr();
}

const Triangle& Triangle::operator=(const Triangle& other)
{
	border = other.border;
	return *this;
}


double Triangle::Area()
{
	double area = 0, p;
	double a, b, c;
	std::vector<Point>& arr = border.GetArr();
	a = Point::distance(arr[0], arr[1]);
	b = Point::distance(arr[1], arr[2]);
	c = Point::distance(arr[2], arr[0]);
	p = (a + b + c) / 2;
	area = sqrt(p * (p - a) * (p - b) * (p - c));
	return area;
}
 

