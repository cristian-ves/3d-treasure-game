#ifndef RANDOM_LIST_H
#define RANDOM_LIST_H

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../utils/CellContent.h"

using namespace std;

template <typename T>
struct NodeRl {
    T data;
    NodeRl<T>* next;
    NodeRl<T>* prev;

    NodeRl(const T &value);
};

template <typename T>
NodeRl<T>::NodeRl(const T &value) : data(value), next(nullptr), prev(nullptr) { }

template <typename T>
class RandomList {
private:
    int size;
    NodeRl<T>* tail;
    NodeRl<T>* front;

    void addNodeLeft(NodeRl<T>* node);
    void addNodeRight(NodeRl<T>* node);

public:
    RandomList();

    void addNode(T value);
    bool isEmpty();
    int getSize();
    void remove(CellContent* cellContent);

    T dequeue();

};

template <typename T>
RandomList<T>::RandomList() : size(0), tail(nullptr), front(nullptr) {
    srand(time(0));
}

template <typename T>
bool RandomList<T>::isEmpty(){
    return (size == 0);
}

template <typename T>
void RandomList<T>::addNodeLeft(NodeRl<T>* node) {
    node->next = tail;
    tail->prev = node;
    tail = node;
}

template <typename T>
void RandomList<T>::addNodeRight(NodeRl<T>* node) {
    front->next = node;
    node->prev = front;
    front = node;
}

template <typename T>
void RandomList<T>::addNode(T value) {
    NodeRl<T>* newNode = new NodeRl<T>(value);

    if (size == 0) {
        tail = front = newNode;
        size = 1;
    } else {
        int pos = rand() % (size + 1);
        if (pos == 0) {
            addNodeLeft(newNode);
        } else if (pos == size) {
            addNodeRight(newNode);
        } else {
            NodeRl<T>* curr = tail;
            for (int i = 0; i < pos; i++) {
                curr = curr->next;
            }
            newNode->prev = curr->prev;
            newNode->next = curr;
            curr->prev->next = newNode;
            curr->prev = newNode;
        }
        size++;
    }
}

template <typename T>
T RandomList<T>::dequeue() {
    // Remove the front element from the random list and return its stored value.
    if(size == 0) return nullptr;
    NodeRl<T>* temp = front;
    front->prev->next = nullptr;
    front = front->prev;

    size--;
    return temp->data;
}

template <typename T>
int RandomList<T>::getSize()
{
    return size;
}

template <typename T>
void RandomList<T>::remove(CellContent* cellContent)
{
    if (cellContent == nullptr) return;
    NodeRl<T>* curr = tail;
    for (int i = 0; i < size; i++)
    {
        if (cellContent == &curr->data->data)
        {
            if (curr->next != nullptr)
                curr->next->prev = curr->prev;
            if (curr->prev != nullptr)
                curr->prev->next = curr->next;
            size--;
            return;
        }
        curr = curr->next;
    }
}

// template <typename T>
// void RandomList<T>::print() {
//     NodeRl<T>* current = tail;
//     while (current != nullptr) {
//         cout << current->data << " ";
//         current = current->next;
//     }
//     cout << "\n";
// }

#endif
