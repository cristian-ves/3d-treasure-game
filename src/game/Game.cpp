#include "Game.h"
#include "Board.h"
#include "../utils/CellContent.h"

void Game::startGame()
{
    board.createBoard();
    board.placeTreasure();
    board.placeElements(0.2, CellContent::ENEMY, "Enemy");
    board.placeElements(0.15, CellContent::TRAP, "Trap");
    board.placeElements(0.1, CellContent::POTION, "Potion");
    board.placeColdHints();
    board.print();
}
