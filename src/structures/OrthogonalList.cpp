#include "OrthogonalList.h"

template <typename T>
NodeOL<T>::NodeOL(const T &value) : data(value), up(nullptr), down(nullptr), left(nullptr), right(nullptr), front(nullptr), back(nullptr) {}

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

    NodeOL<T> *currentLayer = head;
    for (int l = 1; l < layers; l++)
    {
        NodeOL<T> *newFront = new NodeOL<T>(T());
        currentLayer->front = newFront;
        newFront->back = currentLayer;

        currentLayer = newFront;
    }

    NodeOL<T> *currentCol = head;
    for (int c = 1; c < cols; c++)
    {
        NodeOL<T> *newRight = new NodeOL<T>(T());
        currentCol->right = newRight;
        newRight->left = currentCol;

        NodeOL<T> *currentRight = newRight;
        NodeOL<T> *currentLeft = currentCol;

        for (int l = 1; l < layers; l++)
        {
            NodeOL<T> *newFront = new NodeOL<T>(T());
            currentRight->front = newFront;
            newFront->back = currentRight;

            currentLeft = currentLeft->front;
            newFront->left = currentLeft;
            currentLeft->right = newFront;

            currentRight = newFront;
        }

        currentCol = newRight;
    }

    NodeOL<T> *currentRow = head;
    for (int r = 1; r < rows; r++)
    {
        NodeOL<T> *newRow = new NodeOL<T>(T());
        currentRow->down = newRow;
        newRow->up = currentRow;

        NodeOL<T> *currentUp = currentRow;
        NodeOL<T> *currentDown = newRow;

        for (int l = 1; l < layers; l++)
        {
            NodeOL<T> *newLayer = new NodeOL<T>(T());
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
            currentDown->right = newCol;
            newCol->left = currentDown;

            currentUp = currentUp->right;
            currentUp->down = newCol;
            newCol->up = currentUp;

            currentDown = newCol;

            for (int l = 1; l < layers; l++)
            {
                NodeOL<T> *newLayer = new NodeOL<T>(T());
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
int OrthogonalList<T>::getRows() const { return rows; }

template <typename T>
int OrthogonalList<T>::getCols() const { return cols; }

template <typename T>
int OrthogonalList<T>::getLayers() const { return layers; }

template <typename T>
NodeOL<T> *OrthogonalList<T>::getHead() const { return head; }

template class OrthogonalList<int>;
template class OrthogonalList<float>;
