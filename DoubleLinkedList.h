#ifndef DOUBLELINKEDLIST_NODE_H
#define DOUBLELINKEDLIST_NODE_H

#include <iostream>

using namespace std;

namespace DoubleLinkedList {

/**
 * @todo write docs
 */
class Node
{
    Node *prev;
    Node *next;
public:
    Node();

    friend void pushBack(Node **head, Node **tail, Node *node);
    friend void remove(Node **head, Node **tail, Node *node);
};

void pushBack(Node **head, Node **tail, Node *node);
void remove(Node **head, Node **tail, Node *node);

}

#endif // DOUBLELINKEDLIST_NODE_H
