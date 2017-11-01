#ifndef QUEUE_H
#define QUEUE_H

#include "utility.hpp"
#include "Plane.hpp"
#include <iostream>
using namespace std;

class Queue {
public:
	Queue(int limit);
	//void init(int limit);
	Error_code inque(const Plane &item);
	Error_code deque();
	Error_code retrieve(Plane &item) const;
	Plane &operator[](int i);
	int size() const;
	bool empty() const;
	bool full() const;
	~Queue();

private:
	int MAX_SIZE;
	int _size;
	int front;
	int rear;
	Plane *index;
};


#endif
