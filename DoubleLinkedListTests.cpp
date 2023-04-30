#include <iostream>
#include "DoubleLinkedList.cpp"

using namespace std;

int main()
{
    DoubleLinkedList::DLL<int> dll;
    cout << (dll.isEmpty() ? "Pass isEmpty" : "Fail isEmpty") << endl;

    Node<int> *node1 = dll.pushBack(2);
    cout << (node1->getData() == 2 ? "Pass pushBack" : "Fail pushBack") << endl;

    node1->getData() = 10;

    cout << (node1->getData() == 10 ? "Pass pushBack 2" : "Fail pushBack 2") << endl;

    Node<int> *node2 = dll.pushBack(17);
    Node<int> *node3 = dll.pushBack(23);

    // cout << dll << endl; // 10 17 23

    dll.remove(node2);
    cout << (node2 == nullptr ? "Pass remove" : "Fail remove") << endl;

    // cout << dll << endl; // 10 23

    Node<int> *node4 = dll.pushBack(31);
    Node<int> *node5 = dll.pushBack(49);
    Node<int> *node6 = dll.pushBack(72);

    // cout << dll << endl; // 10 23 31 49 72

    dll.remove(node1);
    dll.remove(node6);

    cout << (node1 == nullptr ? "Pass remove 2" : "Fail remove 2") << endl;
    cout << (node6 == nullptr ? "Pass remove 3" : "Fail remove 3") << endl;

    // cout << dll << endl; // 23 31 49
    return 0;
}
