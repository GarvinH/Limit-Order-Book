#ifndef DOUBLELINKEDLIST_NODE_H
#define DOUBLELINKEDLIST_NODE_H

namespace DoubleLinkedList {

template <typename T>
class Node;

template <typename T>
class DLL
{
    Node<T> *head;
    Node<T> *tail;
public:
    DLL();
    ~DLL();
    T& peekFront();
    T& popFront();
    void pushBack(T data);
    void remove(Node<T> &node);
};


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

    friend class DLL<T>;
};

}

#endif // DOUBLELINKEDLIST_NODE_H
