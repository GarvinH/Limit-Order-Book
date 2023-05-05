#include "DoubleLinkedList.h"

using namespace DoubleLinkedList;

DoubleLinkedList::Node::Node()
{
    prev = nullptr;
    next = nullptr;
}

void DoubleLinkedList::pushBack(DoubleLinkedList::Node ** head, DoubleLinkedList::Node ** tail, DoubleLinkedList::Node* node)
{
    if (*head == nullptr)
    {
        *head = node;
        *tail = *head;
        return;
    }

    (*tail)->next = node;
    (*tail)->next->prev = *tail;
    *tail = (*tail)->next;
}

void DoubleLinkedList::remove(DoubleLinkedList::Node ** head, DoubleLinkedList::Node ** tail, DoubleLinkedList::Node* node)
{
    if (node->prev == nullptr && node->next == nullptr)
    {
        return;
    }

    if (node == *head)
    {
        Node *temp = *head;
        *head = (*head)->next;
        temp->next = nullptr;
        return;
    }

    if (node == *tail)
    {
        Node *temp = *tail;
        *tail = (*tail)->prev;
        (*tail)->next = nullptr;
        temp->prev = nullptr;
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = nullptr;
    node->prev = nullptr;
}

