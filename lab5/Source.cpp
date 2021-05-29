#include <iostream>
#include <vector>

template<class ValueType>
class RingBuffer
{
private:
	ValueType* m_data;
	int size_of_array;
	int head = -1;
	int size = 0;

	int next_pos()
	{
		return size == 0 ? 0 : (head + 1) % size_of_array;
	}

	int first_pos()
	{
		return size == 0 ? 0 : (head + size_of_array - size + 1) % size_of_array;
 	}

	int next_left_pos()
	{
		int first = first_pos();
		return first == 0 ? size_of_array - 1 : first - 1;
	}

public:

	RingBuffer(int size = 100) : size_of_array(size)
	{
		m_data = new ValueType[size];
	}

	~RingBuffer() { delete[] m_data; }
	
	void push_back(const ValueType val)
	{
		head = next_pos();
		m_data[head] = val;
		if (size < size_of_array) size++;
	}

	ValueType pop_back()
	{
		if (empty()) throw std::runtime_error("Buffer is empty");
		ValueType tmp = m_data[head];
		head = next_left_pos();
		size--;
		return tmp;
	}
	
	void push_front(const ValueType val)
	{
		int pos = next_left_pos();
		if (size < size_of_array) size++;
		m_data[pos] = value;
	}

	ValueType pop_front() 
	{
		if (empty()) throw std::runtime_error("Buffer is empty");
		ValueType tmp = m_data[first_pos()];
		size--;
		return tmp;
	}

	const ValueType& front() const
	{
		return m_data[first_pos()];
	}

	const ValueType& back() const
	{
		return m_data[head];
	}

	const ValueType& operator[](const int index)
	{
		return m_data[index];
	}

	void capacity(const size_t new_size)
	{
		if (new_size < size_of_array)
		{
			ValueType* new_data = new ValueType[new_size];
			for (int i = 0; i < new_size; i++)
			{
				new_data[i] = m_data[i];
			}
		}
		else if (new_size > size_of_array)
		{
			ValueType* new_data = new ValueType[new_size];
			for (int i = 0; i < size_of_array; i++)
			{
				new_data[i] = m_data[i];
			}
		}
		delete[] m_data;
		m_data = new_data;
	}

	Iterator begin() { return Iterator(*this, &m_data[first_pos()]); }
	Iterator end() { return Iterator(*this, &m_data[head]); }
	
	bool empty()
	{
		return size == 0;
	}

	friend class Iterator<ValueType>;
};

template <class ValueType>
class Iterator
{
private:
	RingBuffer& buffer; 
	size_t pos;
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = ValueType;
	using pointer = ValueType*;
	using reference = ValueType&;

	Iterator(RingBuffer& buf, size_t pos) : buffer(buf), pos(pos) {}

	void operator++()
	{
		pos = (pos + 1) % size;
	}
	

};

int main()
{

}