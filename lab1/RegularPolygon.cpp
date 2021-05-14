#include "RegularPolygon.h"

RegularPolygon::RegularPolygon() : Polygon() {}

RegularPolygon::RegularPolygon(const std::vector<Point>& arr) : Polygon(arr)
{
	std::vector<Point> arr_ = border.GetArr();
	arr_.push_back(arr[0]);
	double side1, side2;
	for (int i = 0; i < arr_.size() - 2; i++)
	{
		side1 = Point::distance(arr[i], arr[i + 1]);
		side2 = Point::distance(arr[i + 1], arr[i + 2]);
		if (side1 != side2)
			throw std::exception("This polygon isn't regular");
	}
}

RegularPolygon::RegularPolygon(const RegularPolygon& other) : Polygon(other)
{
	//border.GetArr() = other.border.GetArr();
}

const RegularPolygon& RegularPolygon::operator=(const RegularPolygon& other)
{
	border = other.border;
	return *this;
}
