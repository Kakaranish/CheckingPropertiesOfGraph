#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include <cstdio>
#include <exception>
#include "Node.h"

template<typename T>
class Stack {
private:
	Node<T> * head = nullptr;
	std::size_t size = 0;
public:
	Stack() = default;

	inline bool empty() const { return size > 0 ? false : true; }
	inline std::size_t getSize() const { return size; }

	void push(T value);
	T top() const;
	void pop();
	void show();
};

#endif