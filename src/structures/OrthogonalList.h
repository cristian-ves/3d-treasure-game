#ifndef ORTHOGONAL_LIST_H
#define ORTHOGONAL_LIST_H

#include <iostream>
using namespace std;

template <typename T>
struct NodeOL
{
    T data;
    NodeOL<T> *up;
    NodeOL<T> *down;
    NodeOL<T> *left;
    NodeOL<T> *right;
    NodeOL<T> *front;
    NodeOL<T> *back;

    NodeOL(const T &value);
};

template <typename T>
class OrthogonalList
{
private:
    NodeOL<T> *head;
    int rows;
    int cols;
    int layers;

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
};

#endif
