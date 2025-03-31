#include "Game.h"
#include "Board.h"

void Game::startGame()
{
    board.createBoard();
    board.placeTreasure();
}
