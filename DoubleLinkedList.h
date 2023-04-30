#ifndef DOUBLELINKEDLIST_NODE_H
#define DOUBLELINKEDLIST_NODE_H

#include <iostream>

using namespace std;

namespace DoubleLinkedList {

template <typename T>
class Node;

template <typename T>
class DLL
{
    Node<T> *head;
    Node<T> *tail;
    void popFront();
public:
    DLL();
    ~DLL();
    bool isEmpty();
    Node<T>* peekFront();
    Node<T>* pushBack(T data);
    void remove(Node<T> *&node);

    template <typename E>
    friend ostream& operator<<(ostream& os, const DLL<E>& dll);
};

template <typename T>
ostream& operator<<(ostream& os, const DLL<T>& dll);

/**
 * @todo write docs
 */
template <typename T>
class Node
{
    Node<T> *prev;
    Node<T> *next;
    T data;
public:
    Node(T data);
    T& getData();

    friend class DLL<T>;

    template <typename E>
    friend ostream& operator<<(ostream& os, const DLL<E>& dll);
};

}

#endif // DOUBLELINKEDLIST_NODE_H
