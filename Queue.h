#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include <cstdio>
#include <exception>
#include "Node.h"

template<typename T>
class Queue {
private:
	Node<T>* head = nullptr;
	std::size_t size = 0;
public:
	Queue() = default;

	inline bool empty() const { return size > 0 ? false : true; }
	inline std::size_t getSize() const { return size; }

	void push(T value);
	void pop();
	T front();
	T back();
	void show();

};

#endif