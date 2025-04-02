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
    NodeOL<CellContent>* getRandomEmptyCell();
    OrthogonalList<CellContent> list;

public:
    Board();

    void createBoard();
    void placeTreasure();
    void placeElements(float percentage, CellContent::Type type, string text);
};

#endif
