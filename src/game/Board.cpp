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

    NodeOL<CellContent>* treasureCell = list.getRandomNode();
    if(treasureCell) {
        treasureCell->data.type = CellContent::TREASURE;
        cout << "Treasure placed at a random empty cell! location: x=" << treasureCell->col << " y=" << treasureCell->row << " z=" << treasureCell->layer << endl;
    }
}

void Board::placeElements(float percentage, CellContent::Type type, string text) {
    int n = round(list.getSize() * percentage);
    for (int i = 0; i < n; i++)
    {
        NodeOL<CellContent>* cell = list.getRandomNode();
        if(cell) {
            cell->data.type = type;
            cout << text << " placed at a random empty cell! location: x=" << cell->col << " y=" << cell->row << " z=" << cell->layer << endl;
        }   
    }
    
}