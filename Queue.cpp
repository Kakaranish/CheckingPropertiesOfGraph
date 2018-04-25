#ifndef _QUEUE_CPP
#define _QUEUE_CPP
#include "Queue.h"

template<typename T>
void Queue<T>::push(T value) {
	if (empty())
		head = new Node<T>(value);
	else {
		Node<T>* tempNode = head;

		while (tempNode->nextNode)
			tempNode = tempNode->nextNode;

		tempNode->nextNode = new Node<T>(value);
	}

	++size;
}


template<typename T>
void Queue<T>::pop() {
	if (empty())
		throw std::range_error("Stack is empty! Unable to .pop()");
	Node<T>* tempNode = head->nextNode;
	delete head;

	head = tempNode;
	--size;
}

template<typename T>
T Queue<T>::front() {
	if (empty())
		throw std::range_error("Stack is empty! Unable to .front()");
	return head->value;
}

template<typename T>
T Queue<T>::back() {
	if (empty())
		throw std::range_error("Stack is empty! Unable to .back()");
	Node<T>* tempNode = head;

	while (tempNode->nextNode)
		tempNode = tempNode->nextNode;

	return tempNode->value;
}

template <typename T>
void Queue<T>::show() {
	if (empty()) {
		std::cout << "Queue is empty" << std::endl;
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