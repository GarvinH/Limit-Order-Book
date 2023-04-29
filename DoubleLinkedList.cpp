#include "DoubleLinkedList.h"
#include <stdio.h>

using namespace DoubleLinkedList;

template<typename T> DoubleLinkedList::DLL<T>::DLL()
{
    head = NULL;
    tail = NULL;
}

template<typename T> T& DoubleLinkedList::DLL<T>::peekFront()
{
    if (head == NULL)
    {
        return NULL;
    }

    return head->data;
}

template<typename T> T& DoubleLinkedList::DLL<T>::popFront()
{
    if (head == NULL)
    {
        return NULL;
    }

    T val = head->data;
    Node<T> *temp = head;
    head = head->next;
    delete temp;

    return val;
}

template<typename T> void DoubleLinkedList::DLL<T>::pushBack(T data)
{
    if (head == NULL)
    {
        head = new Node<T>(data);
        tail = head;
    }

    tail->next = new Node<T>(data);
    tail->next->prev = this;
    tail = tail->next;
}

// assuming that this node belongs to this list....
template<typename T> void DoubleLinkedList::DLL<T>::remove(Node<T> &node)
{
    if (node == head)
    {
        popFront();
        return;
    }

    if (node == tail)
    {
        Node<T> temp = tail;
        tail = tail->prev;
        tail->next = NULL;
        delete temp;
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;

    delete node;
}



template<typename T> DoubleLinkedList::Node<T>::Node(T data)
{
    this->data = data;
    prev = NULL;
    next = NULL;
}
