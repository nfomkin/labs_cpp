#include "Polygon.h"

Polygon::Polygon(const std::vector<Point>& array) : border(array)
{
	if (array.size() < 3)
		throw std::exception("The polygon must consist of 3 or more points");
	//border.GetArr() = array;

	const std::vector<Point>& arr = border.GetArr();
	double product1, product2;

	Point ab = {
		  arr[1].x - arr[0].x,
		  arr[1].y - arr[0].y
	};
	Point bc = {
		  arr[2].x - arr[1].x,
		  arr[2].y - arr[1].y
	};

	for (int i = 2; i < arr.size() - 1; i++)
	{
		product1 = ab.x * bc.y - ab.y * bc.x;
		ab =
		{
		  arr[i].x - arr[i - 1].x,
		  arr[i].y - arr[i - 1].y
		};

		bc =
		{
		  arr[i + 1].x - arr[i].x,
		  arr[i + 1].y - arr[i].y
		};
		product2 = ab.x * bc.y - ab.y * bc.x;

		if ((product1 > 0 and product2 > 0) or (product1 < 0 and product2 < 0))
			continue;
		else
		{
			throw std::exception("The polygon isn't convex");
		}
	}
}

Polygon::Polygon(const Polygon& other) : border(other.border) {}
	//border.GetArr() = other.border.GetArr(); 

Polygon::Polygon() : border({{0,0}, {0,0}, {0,0}})
{
	//border.GetArr() = { {0,0}, {0,0}, {0,0} };
}

const Polygon& Polygon::operator=(const Polygon& other)
{
	border = other.border;
	return *this;
}

void Polygon::PrintCoordinates() const
{
	border.PrintCoordinates();
}

double Polygon::Perimetr() const
{
	return border.Length();
}

double Polygon::Area()
{
	double area = 0.0;
	const std::vector<Point>& arr = border.GetArr();
	for (int i = 0; i < arr.size() - 1; i++)
	{
		area += arr[i].x * arr[i + 1].y;
		area -= arr[i + 1].x * arr[i].y;
	}
	area += arr[arr.size() - 1].x * arr[0].y;
	area -= arr[0].x * arr[arr.size() - 1].y;
	area = 0.5 * abs(area);
	return area;
}
