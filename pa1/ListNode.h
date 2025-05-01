#pragma once

template <class T>

class ListNode {
	ListNode* nextPtr;
	T data;

public:
	ListNode(const T& data);
	~ListNode();

	ListNode<T>* getNextPtr();
	void setNextPtr(ListNode* ptr);

	T& getData();
};

template <class T>
ListNode<T>::ListNode(const T& data) {
	this->data = data;
}

template <class T>
ListNode<T>::~ListNode() {}

template <class T>
ListNode<T>* ListNode<T>::getNextPtr() {
	return this->nextPtr;
}

template <class T>
void ListNode<T>::setNextPtr(ListNode<T>* ptr) {
	this->nextPtr = ptr;
}

template <class T>
T& ListNode<T>::getData() {
	return this->data;
}
