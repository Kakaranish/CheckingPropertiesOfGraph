#ifndef _NODE_H
#define _NODE_H

template<typename T>
struct Node {
public:
	T value;
	Node<T>* nextNode = nullptr;

	Node(T _value, Node<T>* _nextNode = nullptr) : value(_value), nextNode(_nextNode) {}
};

#endif
