#include <vector>
#include <iostream>
//#include <algorithm>

// My comparators and predicates
template<class T>
struct less
{
	bool operator()(T first, T second)
	{
		return first < second;
	}
};

template<class T>
struct greater
{
	bool operator()(T first, T second)
	{
		return first > second;
	}
};

bool Even(int value)
{
	return value % 2 == 0;
}

//

// My class
class Point
{
public:
	int x;
	int y;

	Point(int x = 0, int y = 0) : x(x), y(y) {}

	bool operator==(const Point& other)
	{
		return x == other.x and y == other.y;
	}

	bool operator!=(const Point& other)
	{
		return !(*this == other);
	}

};

//
template<class InputIt, class UnaryPredicate>
bool all_of(InputIt first, InputIt last, UnaryPredicate p)
{
	for (; first != last; first++)
	{
		if (!p(*first))
			return false;
	}
	return true;
}

template<class InputIt, class UnaryPredicate>
bool any_of(InputIt first, InputIt last, UnaryPredicate p)
{
	for (; first != last; first++)
	{
		if (p(*first))
			return true;
	}
	return false;
}

template<class InputIt, class UnaryPredicate>
bool none_of(InputIt first, InputIt last, UnaryPredicate p)
{
	for (; first != last; first++)
	{
		if (p(*first))
		{
			return false;
		}
	}
	return true;
}

template<class InputIt, class UnaryPredicate>
bool one_of(InputIt first, InputIt last, UnaryPredicate p)
{
	bool have = false;
	for (; first != last; first++)
	{
		if (p(*first) and !have)
		{
			have = true;
		}
		else if (p(*first) and have)
		{
			return false;
		}
	}
	return true;
}

template<class InputIt, class Comp = greater<typename std::iterator_traits<InputIt>::value_type>>
bool is_sorted(InputIt first, InputIt last, Comp cmp = {})
{
	if (first == last)
	{
		return true;
	}
	last--;
	for (; first != last; first++)
	{
		if (!cmp(*first, *std::next(first))
			return false;
	}
	return true;
}

template<class InputIt, class UnaryPredicate>
bool is_partitioned(InputIt first, InputIt last, UnaryPredicate p)
{
	while (first != last and p(*first))
		++first;
	while (first != last)
	{
		if (p(*first))
			return false;
		++first;
	}
	return true;
}

template<class InputIt, class T>
InputIt find_not(InputIt first, InputIt last, const T& value)
{
	for (; first != last; first++)
	{
		if (*first != value)
			return first;
	}
	return last;
}

template<class InputIt, class T>
InputIt find_backward(InputIt first, InputIt last, const T& value)
{
	InputIt ans = last;
	for (; first != last; first++)
	{
		if (*first == value)
		{
			ans = first;
		}
	}
	return ans;
}

template<class InputIt, class Predicate>
bool is_palindrome(InputIt first, InputIt last, Predicate p)
{
	InputIt end = last;
	for (; first != end; first++)
	{
		last--;
		if (*first == *last && p(*first))
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

int main()
{
	std::vector<Point> arr{ {5,3},{4,8}, {5,2}, {4,8}, {5,3} };
	auto it = find_not(arr.begin(), arr.end(), Point(5, 3));
	std::cout << (*it).x << " " << (*it).y << '\n';

	if (is_palindrome(arr.begin(), arr.end(), [](Point a) {return a.x > 0 and a.y > 0; }))
	{
		std::cout << "palindrome!" << '\n';
	}

	auto it2 = find_backward(arr.begin(), arr.end(), Point(4, 8));
	std::cout << (*it2).x << " " << (*it2).y << '\n';

	return 0;
}