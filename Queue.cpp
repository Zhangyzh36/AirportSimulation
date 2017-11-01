#include "Queue.hpp"

Queue::Queue(int limit)
{
	MAX_SIZE = limit;
	index = new Plane[limit];
	_size = 0;
	front = 0;
	rear = MAX_SIZE - 1;
	
}


Error_code Queue::inque(const Plane &item)
{
	if ( full() )
		return OVERFLOW;

	rear = (rear + 1) % MAX_SIZE;
	index[rear] = item;
	_size++;

	return SUCCESS;
}

Error_code Queue::deque()
{
	if ( empty() )
		return UNDERFLOW;

	front = (front + 1) % MAX_SIZE;
	_size--;
	
	return SUCCESS;
}

Error_code Queue::retrieve(Plane &item) const
{
	if (_size <= 0) return UNDERFLOW;
	item = index[front];
	return SUCCESS;
}

Plane & Queue::operator[](int i)
{
	return index[(front + i) % MAX_SIZE];
}

int Queue::size() const
{
	return _size;
}

bool Queue::empty() const
{
	return _size == 0;
}

bool Queue::full() const
{
	return _size == MAX_SIZE;
}

Queue::~Queue() {
	if (index)
		delete[] index;
	index = NULL;
}