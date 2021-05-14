#include <iostream>
#include <vector>
#include <map>
#include <ciso646>

class Polynom
{
private:
	std::map<int, double> map;  // key - degree, value - coefficient
public:
	Polynom() {}

	Polynom(const std::multimap<double, int>& multimap) // multimap, т.к идет коэффициент-степень
	{
		for (const auto& element : multimap)
		{
			if (element.second < 0)
				throw "The degree can't be negative";
		}
		for (const auto element : multimap)
		{
			map[element.second] = element.first;
		}
	}

	Polynom(const Polynom& other) : map(other.map) {}

	Polynom& operator=(const Polynom& other)
	{
		if (*this != other)
		{
			map = other.map;
			return *this;
		}
		return *this;
	}

	bool operator==(const Polynom& other) const 
	{
		if (map.size() != other.map.size())
			return false; 
		auto it1 = map.begin();
		auto it2 = other.map.begin();
		while (it1 != map.end())
		{
			if ((it1->first != it2->first) or (it1->second != it2->second))
				return false;
			it1++;
			it2++;
		}
		return true;
	}

	bool operator!=(const Polynom& other) const 
	{
		return not(*this == other);
	}

	Polynom operator+(const Polynom& other) const 
	{
		return Polynom(*this) += other;
	}

	Polynom operator-(const Polynom& other) const 
	{
		return Polynom(*this) -= other;
	}

	Polynom operator-() const 
	{
		Polynom temp;
		for (const auto& pair : map)
		{
			temp.map[pair.first] = -1 * pair.second;
		}
		return temp;
	}

	Polynom& operator+=(const Polynom& other)
	{
		int degree; 
		double coeff;
		for (const auto& pair : other.map)
		{
			degree = pair.first;
			coeff = pair.second;
			map[degree] += coeff;
		}
		return *this;
	}

	Polynom& operator-=(const Polynom& other)
	{
		int degree;
		double coeff;
		for (const auto& pair : other.map)
		{
			degree = pair.first;
			coeff = pair.second;
			map[degree] -= coeff;
		}
		return *this;
	}

	Polynom operator*(int num) const 
	{
		int degree;
		double coeff;
		Polynom temp;
		for (const auto& pair : map)
		{
			degree = pair.first;
			coeff = pair.second;
			temp.map[degree] = coeff * num;
 		}
		return temp;
	}

	Polynom operator*(const Polynom& other) const 
	{
		return Polynom(*this) *= other;
	}

	Polynom operator/(int number) const 
	{
		return Polynom(*this) /= number;
	}

	Polynom& operator*=(const Polynom& other)
	{
		Polynom temp;
		int degree;
		double coeff;
		for (const auto& pair1 : map)
		{
			for (const auto& pair2 : other.map)
			{
				coeff = pair1.second * pair2.second;
				degree = pair1.first + pair2.first;
				temp.map[degree] += coeff;
			}
		}
		return *this = temp;
	}

	Polynom& operator/=(int number)
	{
		int degree;
		double coeff;
		for (const auto& pair : map)
		{
			degree = pair.first;
			coeff = pair.second;
			map[degree] = coeff / number;
		}
		return *this;
	}

	double operator[](int degree) 
	{
		return map[degree];
	}

	friend std::ostream& operator<<(std::ostream& out, const Polynom& polynom);
	friend std::istream& operator>>(std::istream& in, Polynom& polynom);

};

std::ostream& operator<<(std::ostream& out, const Polynom& polynom) 
{
	auto it_end = polynom.map.end();
	auto it_begin = polynom.map.begin();
	it_end--;
	if (it_end->second != 0)
		out << it_end->second << "x^" << it_end->first << " ";
	it_end--;
	it_begin--;
	for (it_end; it_end != it_begin; it_end--)
	{
		if (it_end->first == 0)
		{
			if (it_end->second > 0)
				out << "+ " << it_end->second << " ";
			else if (it_end->second < 0)
				out << "- " << -1 * it_end->second << " ";
		}
		else if (it_end->second < 0)
			out << "- " << -1 * it_end->second << "x^" << it_end->first << " ";
		else if (it_end->second > 0)
			out << "+ " << it_end->second << "x^" << it_end->first << " ";

	}
	out << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, Polynom& polynom)
{
	int k, degree;
	double coeff;
	in >> k;
	for (int i = 0; i < k; i++)
	{
		in >> coeff >> degree;
		polynom.map[degree] = coeff;
	}
	return in;
}

int main()
{
	Polynom a({{ 1,2 }, { 1,0 }});
	Polynom b({ {3,3}, {1,1} });
	std::cout << a + b << std::endl << b - a;
	return 0;
}