#include "DoubleLinkedList.h"

using namespace DoubleLinkedList;

template<typename T> std::ostream & DoubleLinkedList::operator<<(std::ostream& os, const DLL<T>& dll)
{
    Node<T> *temp = dll.head;
    while (temp != nullptr)
    {
        os << temp->data;

        if (temp->next != nullptr)
        {
           os << " ";
        }

        temp = temp->next;
    }

    return os;
}

template<typename T> DoubleLinkedList::DLL<T>::DLL()
{
    head = nullptr;
    tail = nullptr;
}

template<typename T> DoubleLinkedList::DLL<T>::~DLL()
{
    while (head != nullptr)
    {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T> bool DoubleLinkedList::DLL<T>::isEmpty()
{
    return head == nullptr;
}


template<typename T> Node<T>* DoubleLinkedList::DLL<T>::peekFront()
{
    return head;
}

template<typename T> void DoubleLinkedList::DLL<T>::popFront()
{
    Node<T> *temp = head;
    head = head->next;
    temp->next = nullptr;
    delete temp;
}

template<typename T> Node<T>* DoubleLinkedList::DLL<T>::pushBack(T data)
{
    if (head == nullptr)
    {
        head = new Node<T>(data);
        tail = head;
        return head;
    }

    tail->next = new Node<T>(data);
    tail->next->prev = tail;
    tail = tail->next;
    return tail;
}

// assuming that this node belongs to this list....
template<typename T> void DoubleLinkedList::DLL<T>::remove(Node<T> *&node)
{
    if (node == head)
    {
        popFront();
        node = nullptr;
        return;
    }

    if (node == tail)
    {
        Node<T> *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        temp->prev = nullptr;
        delete temp;
        node = nullptr;
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = nullptr;
    node->prev = nullptr;

    delete node;
    node = nullptr;
}

template<typename T> DoubleLinkedList::Node<T>::Node(T data)
{
    this->data = data;
    prev = nullptr;
    next = nullptr;
}

template<typename T> T& DoubleLinkedList::Node<T>::getData()
{
    return data;
}
