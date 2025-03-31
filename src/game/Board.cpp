#include "Board.h"

#include <cstdlib>
#include <ctime>

Board::Board() : list(1,1,1){

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
    srand(time(0));

    NodeOL<CellContent>* treasureCell = getRandomEmptyCell();
    if(treasureCell) {
        treasureCell->data.type = CellContent::TREASURE;
        cout << "Treasure placed at a random empty cell! location: x=" << treasureCell->col << " y=" << treasureCell->row << " z=" << treasureCell->layer << endl;
        cout << CellContent::getTypeText(treasureCell->data.type) << endl;
    }
}

NodeOL<CellContent>* Board::getRandomEmptyCell() {
    NodeOL<CellContent>* cell;
    do {
        int x = rand() % list.getCols();
        int y = rand() % list.getRows();
        int z = rand() % list.getLayers();
        cell = list.getNode(x,y,z);
    } while(cell == nullptr || cell->data.type != CellContent::EMPTY);

    return cell;
}