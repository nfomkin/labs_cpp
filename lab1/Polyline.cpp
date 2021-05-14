#include "Polyline.h"

Polyline::Polyline() = default;

Polyline::Polyline(const std::vector<Point>& arr) : arr(arr) {}

Polyline::Polyline(const Polyline & other) : arr(other.arr) {}

const Polyline& Polyline::operator=(const Polyline& other)  
{
	arr = other.arr;
	return *this;
}

void Polyline::PrintCoordinates() const 
{
	for (auto coordinate : arr)
	{
		std::cout << "x = " << coordinate.x << "\t" << "y = " << coordinate.y << '\n';
	}
}

void Polyline::AddCoordinate(int x, int y)
{
	arr.push_back({ x, y });
}

double Polyline::Length() const 
{
	double length = 0;
	for (int i = 0; i < arr.size() - 1; i++)
	{
		length += Point::distance(arr[i], arr[i + 1]);
	}
	return length;
}
