#ifndef ORTHOGONAL_LIST_H
#define ORTHOGONAL_LIST_H

#include "RandomList.h"

#include <iostream>
using namespace std;

template <typename T>
struct NodeOL
{
    T data;
    NodeOL<T> *up, *down, *left, *right, *front, *back;

    int col, row, layer;

    NodeOL(const T &value);
};

template <typename T>
NodeOL<T>::NodeOL(const T &value) : data(value), up(nullptr), down(nullptr), left(nullptr), right(nullptr), front(nullptr), back(nullptr) {}

template <typename T>
class OrthogonalList
{
private:
    NodeOL<T> *head;
    int rows, cols, layers;
    RandomList<NodeOL<T>*> randomList;

    void initializeEmptyList();

public:
    OrthogonalList(int rows, int cols, int layers);

    void setCell(int row, int col, int layer, const T &value);
    T &getCell(int row, int col, int layer) const;
    NodeOL<T> *getNode(int row, int col, int layer) const;

    int getRows() const;
    int getCols() const;
    int getLayers() const;
    NodeOL<T> *getHead() const;

    NodeOL<T> *getRandomNode();
    int getSize();
};

template <typename T>
OrthogonalList<T>::OrthogonalList(int rows, int cols, int layers) : head(nullptr), rows(rows), cols(cols), layers(layers)
{
    initializeEmptyList();
}

template <typename T>
void OrthogonalList<T>::initializeEmptyList()
{
    if (head)
        return; // Prevent re-initialization

    head = new NodeOL<T>(T());
    head->col = 0;
    head->row = 0;
    head->layer = 0;
    randomList.addNode(head);

    // Creating first layer
    NodeOL<T> *currentLayer = head;
    for (int l = 1; l < layers; l++)
    {
        NodeOL<T> *newFront = new NodeOL<T>(T());
        newFront->row = 0;
        newFront->col = 0;
        newFront->layer = l;
        randomList.addNode(newFront);
        
        currentLayer->front = newFront;
        newFront->back = currentLayer;

        currentLayer = newFront;
    }

    // Creating the first row in each layer
    NodeOL<T> *currentCol = head;
    for (int c = 1; c < cols; c++)
    {
        NodeOL<T> *newRight = new NodeOL<T>(T());
        newRight->row = 0;
        newRight->col = c;
        newRight->layer = 0;
        randomList.addNode(newRight);

        currentCol->right = newRight;
        newRight->left = currentCol;

        NodeOL<T> *currentRight = newRight;
        NodeOL<T> *currentLeft = currentCol;

        for (int l = 1; l < layers; l++)
        {
            NodeOL<T> *newFront = new NodeOL<T>(T());
            newFront->row = 0;
            newFront->col = c;
            newFront->layer = l;
            randomList.addNode(newFront);

            currentRight->front = newFront;
            newFront->back = currentRight;

            currentLeft = currentLeft->front;
            newFront->left = currentLeft;
            currentLeft->right = newFront;

            currentRight = newFront;
        }

        currentCol = newRight;
    }

    // Creating remaining rows and connecting them
    NodeOL<T> *currentRow = head;
    for (int r = 1; r < rows; r++)
    {
        NodeOL<T> *newRow = new NodeOL<T>(T());
        newRow->row = r;
        newRow->col = 0;
        newRow->layer = 0;
        randomList.addNode(newRow);

        currentRow->down = newRow;
        newRow->up = currentRow;

        NodeOL<T> *currentUp = currentRow;
        NodeOL<T> *currentDown = newRow;

        for (int l = 1; l < layers; l++)
        {
            NodeOL<T> *newLayer = new NodeOL<T>(T());
            newLayer->row = r;
            newLayer->col = 0;
            newLayer->layer = l;
            randomList.addNode(newLayer);

            newLayer->back = currentDown;
            currentDown->front = newLayer;

            currentUp = currentUp->front;
            newLayer->up = currentUp;
            currentUp->down = newLayer;

            currentDown = newLayer;
        }

        currentUp = currentRow;
        currentDown = newRow;

        for (int c = 1; c < cols; c++)
        {
            NodeOL<T> *newCol = new NodeOL<T>(T());
            newCol->row = r;
            newCol->col = c;
            newCol->layer = 0;
            randomList.addNode(newCol);

            currentDown->right = newCol;
            newCol->left = currentDown;

            currentUp = currentUp->right;
            currentUp->down = newCol;
            newCol->up = currentUp;

            currentDown = newCol;

            for (int l = 1; l < layers; l++)
            {
                NodeOL<T> *newLayer = new NodeOL<T>(T());
                newLayer->row = r;
                newLayer->col = c;
                newLayer->layer = l;
                randomList.addNode(newLayer);

                newLayer->back = currentDown;
                currentDown->front = newLayer;

                if (currentUp->front)
                {
                    currentUp = currentUp->front;
                    newLayer->up = currentUp;
                    currentUp->down = newLayer;
                }

                if (currentDown->left && currentDown->left->front)
                {
                    currentDown->left->front->right = newLayer;
                    newLayer->left = currentDown->left->front;
                }

                currentDown = newLayer;
            }
        }

        currentRow = currentRow->down;
    }
}

template <typename T>
void OrthogonalList<T>::setCell(int row, int col, int layer, const T &value)
{
    NodeOL<T> *node = getNode(row, col, layer);
    if (node)
        node->data = value;
}

template <typename T>
T &OrthogonalList<T>::getCell(int row, int col, int layer) const
{
    NodeOL<T> *node = getNode(row, col, layer);
    if (!node)
        throw out_of_range("Invalid cell coordinates.");
    return node->data;
}

template <typename T>
NodeOL<T> *OrthogonalList<T>::getNode(int row, int col, int layer) const
{
    if (row < 0 || row >= rows || col < 0 || col >= cols || layer < 0 || layer >= layers)
        return nullptr;

    NodeOL<T> *current = head;
    for (int r = 0; r < row; r++)
        current = current->down;
    for (int c = 0; c < col; c++)
        current = current->right;
    for (int l = 0; l < layer; l++)
        current = current->front;

    return current;
}

template <typename T>
int OrthogonalList<T>::getSize() {
    return cols * rows * layers;
}

template <typename T>
NodeOL<T>* OrthogonalList<T>::getRandomNode() {
    return randomList.enqueue();
}

template <typename T>
int OrthogonalList<T>::getRows() const { return rows; }

template <typename T>
int OrthogonalList<T>::getCols() const { return cols; }

template <typename T>
int OrthogonalList<T>::getLayers() const { return layers; }

template <typename T>
NodeOL<T> *OrthogonalList<T>::getHead() const { return head; }

#endif
