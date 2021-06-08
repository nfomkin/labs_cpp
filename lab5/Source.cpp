#include <iostream>
#include <algorithm>

template<class ValueType>
class RingBuffer;
template<class ValueType>
class Iterator;


template <class ValueType>
class RingBuffer
{
	typedef Iterator<const ValueType> const_iterator;
	typedef Iterator<ValueType> iterator;
private:
	ValueType* data;
	int head = -1;
	int real_size;
	int size_of_array;
	int size = 0;

	int next_pos(int cur)
	{
		return (cur + 1) % size_of_array;
	}

	int first_pos()
	{
		return (head + (size_of_array - size) + 1) % size_of_array;
	}

	int next_left_pos(int cur)
	{
		return cur == 0 ? size_of_array - 1 : cur - 1;
	}

	bool empty()
	{
		return size == 0;
	}

public:
	explicit RingBuffer(int size) : size_of_array(size + 1), real_size(size)
	{
		data = new ValueType[size + 1];
	}

	~RingBuffer()
	{
		delete[] data;
	}

	void push_back(const ValueType& el)
	{
		head = next_pos(head);
		data[head] = el;
		if (size != real_size) size++;
	}

	void pop_back()
	{
		if (empty())
			return;
		head = next_left_pos(head);
		size--;
	}

	void push_front(const ValueType& el)
	{
		int pos = next_left_pos(first_pos());
		if (size == real_size)
		{
			data[pos] = el;
			head = next_left_pos(head);
		}
		else
		{
			data[pos] = el;
			size++;
		}
	}

	void pop_front()
	{
		if (empty())
			return;
		size--;
	}

	const ValueType& back()
	{
		if (empty()) throw std::runtime_error("Buffer is empty");

		return data[head];
	}

	const ValueType& front()
	{
		if (empty()) throw std::runtime_error("Buffer is empty");

		return data[first_pos()];
	}

	const ValueType& operator[](int index)
	{
		if (index >= size) throw std::runtime_error("out of range");
		return data[(first_pos() + index) % size_of_array];
	}

	void capacity(int new_size)
	{
		int first = first_pos();
		ValueType* new_data = new ValueType[new_size + 1];
		if (new_size + 1 < size_of_array)
		{
			int i;
			for (i = 0; i < std::min(size, new_size); i++)
			{
				new_data[i] = data[first];
				first = next_pos(first);
			}
			head = i - 1;
			size_of_array = new_size + 1;
			real_size = new_size;
			size = std::min(size, new_size);
		}
		else if (new_size + 1 > size_of_array)
		{
			int i;
			for (i = 0; i < size; i++)
			{
				new_data[i] = data[first];
				first = next_pos(first);
			}
			head = i - 1;
			size_of_array = new_size + 1;
			real_size = new_size;
		}

		delete[] data;
		data = new_data;
	}

	void print_buffer()
	{
		int first = first_pos();
		for (int i = 0; i < size; i++)
		{
			std::cout << data[first] << " ";
			first = next_pos(first);
		}
		std::cout << '\n';
	}

	void print_array()
	{
		for (int i = 0; i < size_of_array; i++)
		{
			std::cout << data[i] << " ";
		}
		std::cout << '\n';
	}

	iterator begin() const { return iterator(*this, first_pos()); }
	iterator end() const { return iterator(*this, next_pos(head)); }

	const_iterator cbegin() const { return const_iterator(*this, first_pos()); }
	const_iterator cend() const { return const_iterator(*this, next_pos(head)); }

	friend class Iterator<ValueType>;
};


template<class ValueType>
class Iterator
{
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = ValueType;
	using reference = ValueType&;
	using pointer = ValueType*;

private:
	RingBuffer<ValueType>& buffer;
	int pos;
public:
	Iterator(RingBuffer<ValueType>& buf, const int& pos) : buffer(buf), pos(pos) {}

	Iterator& operator=(const Iterator& other)
	{
		buffer = other.buffer;
		pos = other.pos;
		return *this;
	}

	reference operator*()
	{
		return buffer.data[pos];
	}

	pointer operator->()
	{
		return &(operator*());
	}

	Iterator& operator++()
	{
		pos = (pos + 1) % buffer.size_of_array;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator tmp = *this;
		pos = (pos + 1) % buffer.size_of_array;
		return tmp;
	}

	Iterator& operator--()
	{
		pos = pos == 0 ? buffer.size_of_array - 1 : pos - 1;
		return *this;
	}

	Iterator operator--(int)
	{
		Iterator tmp = *this;
		pos = pos == 0 ? buffer.size_of_array - 1 : pos - 1;
		return tmp;
	}

	Iterator operator+(const int& num)
	{
		Iterator tmp = *this;
		tmp.pos = (pos + num) % buffer.size_of_array;
		return tmp;
	}

	reference operator[](const int& index)
	{
		return buffer.data[(*this + index).pos];
	}

	friend Iterator<ValueType> operator+(const int& num, const Iterator<ValueType>& it);


	difference_type operator-(const Iterator& other) const 
	{
		int a = pos;
		int b = other.pos;

		if (buffer.first_pos() > buffer.head)
		{
			if (a < buffer.first_pos())
				a += buffer.size_of_array;
			if (b < buffer.first_pos())
				b += buffer.size_of_array;
			return a - b;
		}
		return a - b;
	}

	Iterator operator-(const int& num)
	{
		Iterator tmp = *this;
		tmp.pos = num - pos;
		return tmp;
	}

	Iterator& operator+=(const int& num)
	{
		pos = (pos + num) % buffer.size_of_array;
		return *this;
	}

	Iterator& operator-=(const int& num)
	{
		if (pos - num < 0)
		{
			pos = buffer.size_of_array + pos - num;
			return *this;
		}
		pos -= num;
		return *this;
	}

	bool operator<(const Iterator& other)
	{
		return (*this - buffer.begin()) < (other - buffer.begin());
	}

	bool operator>(const Iterator& other)
	{
		return (*this - buffer.begin()) > (other - buffer.begin());
	}

	bool operator<=(const Iterator& other)
	{
		return (*this - buffer.begin()) <= (other - buffer.begin());
	}

	bool operator>=(const Iterator& other)
	{
		return (*this - buffer.begin()) >= (other - buffer.begin());
	}

	bool operator==(const Iterator& other)
	{
		return pos == other.pos;
	}

	bool operator!=(const Iterator& other)
	{
		return pos != other.pos;
	}
};

template<class ValueType>
Iterator<ValueType> operator+(const int& num, const Iterator<ValueType>& it)
{
	Iterator<ValueType> tmp = *this;
	tmp.pos += num;
	return tmp;
}

int main()
{
	RingBuffer<int> a(3);
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.print_array();
	a.print_buffer();

	a.capacity(4);
	a.push_front(84);
	a.push_front(33);
	a.print_array();
	a.print_buffer();

	auto it = a.begin();
	std::cout << *it << '\n';

	std::cout << "max_element = " << *(std::max_element(a.begin(), a.end())) << '\n';
	std::cout << "min_elememt = " << *(std::min_element(a.begin(), a.end())) << '\n';
	std::sort(a.begin(), a.end());
	return 0; 
}
