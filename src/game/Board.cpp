#include "Board.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

Board::Board() : list(1,1,1){
    srand(time(0));
}

void Board::getDimensionValue(int &n, string text)
{
    do
    {
        cout << text;
        cin >> n;
        if (n < 2)
            cout << "Invalid entry! The dimension must be at least 2." << endl;
    } while (n < 2);
}

void Board::createBoard()
{
    int x, y, z;

    cout << "\nLet's create the 3D board!\n";
    getDimensionValue(x, "Enter X dimension: ");
    getDimensionValue(y, "Enter Y dimension: ");
    getDimensionValue(z, "Enter Z dimension: ");

    list = OrthogonalList<CellContent>(x, y, z);
}

void Board::placeTreasure() {
    treasureCell = list.getRandomNode();
    if(treasureCell) {
        treasureCell->data.type = CellContent::TREASURE;
        cout << "Treasure placed at a random empty cell! location: x=" << treasureCell->col << " y=" << treasureCell->row << " z=" << treasureCell->layer << endl;
    }
    placeHints();
}

void Board::placeElements(float percentage, CellContent::Type type, string text) {
    int n = round(list.getSize() * percentage);
    for (int i = 0; i < n; i++)
    {
        NodeOL<CellContent>* cell = list.getRandomNode();
        if (cell->data.type == CellContent::TREASURE || cell->data.type == CellContent::HINT)
        {
            i--;
        } else if(cell) {
            cell->data.type = type;
            cout << text << " placed at a random empty cell! location: x=" << cell->col << " y=" << cell->row << " z=" << cell->layer << endl;
        }   
    }
}

void Board::placeHints(){
    applyHotHint(treasureCell->front);
    applyHotHint(treasureCell->back);
    applyHotHint(treasureCell->right);
    applyHotHint(treasureCell->left);
    applyHotHint(treasureCell->up);
    applyHotHint(treasureCell->down);
}

void Board::applyHotHint(NodeOL<CellContent>* adjacentNode) {
    if (!adjacentNode) return;

    adjacentNode->data.type = CellContent::HINT;
    adjacentNode->data.hint = CellContent::HOT;
    list.getRandomList()->remove(&adjacentNode->data);


    NodeOL<CellContent>* neighbors[] = {
        adjacentNode->front,
        adjacentNode->back,
        adjacentNode->right,
        adjacentNode->left,
        adjacentNode->up,
        adjacentNode->down
    };

    for (int i = 0; i < 6; i++){
        NodeOL<CellContent>* neighbor = neighbors[i];
        applyWarmHint(neighbor);
    }
}

void Board::applyWarmHint(NodeOL<CellContent>* adjacentNode) {
    if (adjacentNode != nullptr && adjacentNode->data.type != CellContent::TREASURE && adjacentNode->data.type != CellContent::HINT) {
        adjacentNode->data.type = CellContent::HINT;
        adjacentNode->data.hint = CellContent::WARM;
        list.getRandomList()->remove(&adjacentNode->data);
    }
}

void Board::placeColdHints()
{
    RandomList<NodeOL<CellContent>*>* randomList = list.getRandomList();
    int n = floor(randomList->getSize() / 2);

    for (int i = 0; i < n; i++)
    {
        NodeOL<CellContent>* cell = list.getRandomNode();
        cell->data.type = CellContent::HINT;
        cell->data.hint = CellContent::COLD;
    }
}

void Board::print()
{
    list.print();
}
