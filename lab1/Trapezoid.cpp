#include "Trapezoid.h"

Trapezoid::Trapezoid() : Polygon({ {0,0}, {0,0}, {0,0}, {0,0} })
{
	//border.GetArr() = { {0,0}, {0,0}, {0,0}, {0,0} };
}

Trapezoid::Trapezoid(const std::vector<Point>& arr) : Polygon(arr)
{
	if (border.GetArr().size() != 4)
		throw std::exception("The trapezoid must consist of 4 points");
}

Trapezoid::Trapezoid(const Trapezoid& other) : Polygon(other)
{
	//border.GetArr() = other.border.GetArr();
}

const Trapezoid& Trapezoid::operator=(const Trapezoid& other) 
{
	border = other.border;
	return *this;
}

