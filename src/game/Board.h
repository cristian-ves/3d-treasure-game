#ifndef BOARD_H
#define BOARD_H

#include "../structures/OrthogonalList.h"
#include <iostream>

using namespace std;

class Board
{
private:
    void getDimensionValue(int &n, string text);

public:
    void createBoard();
};

#endif
