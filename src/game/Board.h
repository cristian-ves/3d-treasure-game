#ifndef BOARD_H
#define BOARD_H

#include "../structures/OrthogonalList.h"
#include "../utils/CellContent.h"
#include <iostream>

using namespace std;

class Board
{
private:
    void getDimensionValue(int &n, string text);
    OrthogonalList<CellContent> list;
    NodeOL<CellContent>* treasureCell;
    void applyHotHint(NodeOL<CellContent>* adjacentNode);
    void applyWarmHint(NodeOL<CellContent>* adjacentNode);

public:
    Board();

    void createBoard();
    void placeTreasure();
    void placeElements(float percentage, CellContent::Type type, string text);
    void placeHints();
    void placeColdHints();
    void print();
};

#endif
