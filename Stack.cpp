#ifndef _STACK_CPP
#define _STACK_CPP

#include "Stack.h"
template<typename T>
void Stack<T>::push(T value) {
	Node<T>* tempNode = new Node<T>(value);

	if (empty())
		head = tempNode;
	else {
		tempNode->nextNode = head;
		head = tempNode;
	}
	++size;
}

template<typename T>
T Stack<T>::top() const {
	if (empty())
		throw std::range_error("Stack is empty! Unable to .top()");
	return head->value;
}

template<typename T>
void Stack<T>::pop() {
	if (empty())
		throw std::range_error("Stack is empty! Unable to .pop()");
	Node<T>* tempNode = head->nextNode;
	delete head;
	head = tempNode;
	
	--size;
}
template<typename T>
void Stack<T>::show() {
	if (empty()) {
		std::cout << "Stack is empty" << std::endl;
		return;
	}

	Node<T>* tempNode = head;
	std::cout << "Stack: " << std::endl;
	while (tempNode) {
		std::cout << tempNode->value << "\t";
		tempNode = tempNode->nextNode;
	}
	std::cout << std::endl;
}

#endif