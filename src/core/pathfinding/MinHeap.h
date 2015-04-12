#include <iostream>
using namespace std;

template <typename Comparable>

class MinHeap
{
private:
	int m_currentSize;
	vector<Comparable> m_list;	//elements start at index 1

public:
	explicit MinHeap( int capacity )
	{
		m_currentSize = 0;

		//resizes the array to the size of capacity
		m_list.resize( capacity );
	};


	~MinHeap()
	{

	};


	//returns true if no elements are in the heap and false if there are.
	bool empty() const
	{
		if ( m_currentSize <= 0 )
			return true;
		else
			return false;
	};
	

	//Returns and removes the smallest item in the heap ( the root )
	Comparable getMin()
	{
		if ( m_currentSize <= 0 )
			throw std::underflow_error("Can't return an element from an empty heap");

		Comparable minElement = m_list[1];

		m_list[1] = m_list[m_currentSize];
		m_currentSize--;

		int hole = 1;
		Comparable temp = m_list[1];
		int child;

		while ( hole * 2 <= m_currentSize )
		{
			child = hole * 2;

			if (child != m_currentSize && m_list[child + 1] < m_list[child])
				child++;

			if ( m_list[child] < temp )
			{
				m_list[hole] = m_list[child];
				hole = child;
			}
			else
			{
				break;
			}
		}

		m_list[hole] = temp;

		return minElement;
	};


	//inserts the element 'x' into the heap
	void insert( Comparable x )
	{
		if ( m_currentSize == m_list.size() - 1 )
			m_list.resize( 2 * m_list.size() + 1 );

		m_currentSize++;
		int hole = m_currentSize;

		while ( hole > 1 && x < m_list[hole / 2] )
		{
			m_list[hole] = m_list[hole / 2];
			hole /= 2;
		}

		m_list[hole] = x;
	};
};