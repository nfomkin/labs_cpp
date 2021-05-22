#include <iostream>
#include <vector>

template<class ValueType>
class RingBuffer
{
private:
	ValueType m_data[size];
	const int size;
public:
	class Iterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = ValueType;
		using pointer = ValueType*;
		using reference = ValueType&;

		Iterator(pointer ptr) : m_ptr(ptr) {}

		reference operator*() const { return *m_ptr; }
		pointer opearator->() { return m_ptr; }

		Iterator& operator++() { m_ptr++; return *this; }

		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

		friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

		reference operator[](const int index)
		{
			return *(m_ptr + index);
		}

		void operator+=(const int n)
		{
			m_ptr += n;
		}

		void operator-=(const int n)
		{
			m_ptr -= n;
		}

		Iterator operator+(const int n)
		{
			return *this + n;
		}

		Iterator operator-(const int n)
		{
			return *this - n;
		}

		int operator-(const Iterator& other)
		{
			return m_ptr - other.m_ptr;
		}

		bool operator<(const Iterator& other)
		{
			return m_ptr < other.m_ptr;
		}

		bool operator>(const Iterator& other)
		{
			return m_ptr > other.m_ptr;
		}

		bool operator<=(const Iterator& other)
		{
			return m_ptr <= other.m_ptr;
		}

		bool operator>=(const Iterator& other)
		{
			return m_ptr >= other.m_ptr;
		}
	private:
		pointer m_ptr;
	};

	RingBuffer(int size) : size(size) {}
	RingBuffer() : size(100) {}
	void push_back(ValueType& value)
	{
		
	}
	Iterator begin() { return Iterator(&m_data[0]); }
	Iterator end() { return Iterator(&m_data[200]); }
};

int main()
{
	RingBuffer<int> a;
	
}