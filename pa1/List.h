#pragma once
#include "ListNode.h"

template <class T>

class List {
ListNode<T>* front;

public:
    List();
    ~List();
    void insertAtFront(const T& data);
    ListNode<T>* getFront();
    bool deleteNode(T& searchData);
    bool isEmpty();
};

template <class T>
inline List<T>::List() {
}

template <class T>
inline List<T>::~List() {
    if (isEmpty()) return;

    ListNode<T>* cur = getFront();
    this->front = nullptr;
    while (cur->getNextPtr() != nullptr) {
        ListNode<T>* old = cur;
        cur = cur->getNextPtr();
        // delete old;
    }
}

template <class T>
inline void List<T>::insertAtFront(const T &data) {
    // ListNode<T>* newNode = new ListNode<T>(data);
    // newNode->setNextPtr(getFront());
    // this->front = newNode;
}

template <class T>
inline ListNode<T> *List<T>::getFront()
{
    return this->front;
}

template <class T>
inline bool List<T>::deleteNode(T &searchData)
{
    return false;
}

template <class T>
inline bool List<T>::isEmpty()
{
    return getFront() == nullptr;
}
