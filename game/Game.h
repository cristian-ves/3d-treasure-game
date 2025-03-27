#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <sstream>
#include "Board.h"

using namespace std;

class Game
{
private:
    Board board;

public:
    void startGame()
    {
        board.createBoard();
    }
};

#endif