#include "ClosedPolyline.h"

ClosedPolyline::ClosedPolyline() : Polyline() {}

ClosedPolyline::ClosedPolyline(const std::vector<Point>& arr) : Polyline(arr) {}

ClosedPolyline::ClosedPolyline(const ClosedPolyline& other) : Polyline(other) {}

const ClosedPolyline& ClosedPolyline::operator=(const ClosedPolyline& other)
{
	arr = other.arr;
	return *this;
}

void ClosedPolyline::PrintCoordinates() const 
{
	Polyline::PrintCoordinates();
	std::cout << "x = " << arr.back().x << "\t" << "y = " << arr.back().y << '\n';
}

double ClosedPolyline::Length() const 
{
	return Polyline::Length() + Point::distance(arr.back(), arr.front());
}

const std::vector<Point>& ClosedPolyline::GetArr() const
{
	return arr;
}
