#ifndef BOARD_H
#define BOARD_H

#include "../structures/OrthogonalList.h"

using namespace std;

class Board
{
private:
    void getDimensionValue(int &n, string text)
    {
        do
        {
            cout << text;
            cin >> n;
            if (n < 2)
                cout << "Invalid entry! The dimension must be at least 2."
                     << endl;
        } while (n < 2);
    }

public:
    void createBoard()
    {
        int x, y, z;

        cout << "\nLet's create the 3D board!\n";
        getDimensionValue(x, "Enter X dimension: ");
        getDimensionValue(y, "Enter Y dimension: ");
        getDimensionValue(z, "Enter Z dimension: ");

        OrthogonalList<int> list(x, y, z);
    }
};

#endif