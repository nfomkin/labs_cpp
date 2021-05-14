#include <iostream>
#include "Polygon.h"
#include "Triangle.h"
#include "Trapezoid.h"
#include "RegularPolygon.h"

int main()
{
	try {
		Polygon a({ {2,1}, {4,5}, {54,43 }, {43,64} });
		std::cout << "S = " << a.Area() << "P = " << a.Perimetr() ;
		a.PrintCoordinates();
	}
	catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << '\n';
	}

	try {
		Triangle b({ {3,2}, {7,5}, {0,0} });
		std::cout << "S = " << b.Area() << " "  << "P = " << b.Perimetr() << '\n';
	}
	catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << '\n';
	}

	try {
		Trapezoid c({ {3,2}, {7,5}, {0,0} });
		std::cout << "S = " << c.Area() << "P = " << c.Perimetr();
	}
	catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << '\n';
	}

	try {
		RegularPolygon d({ {6,4}, {8,5}, {4,8} });
		std::cout << "S = " << d.Area();
	}
	catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << '\n';
	}
}