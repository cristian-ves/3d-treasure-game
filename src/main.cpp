#include "game/Game.h"

#include <iostream>

using namespace std;

int main()
{
    int choice;
    Game game;

    do
    {
        cout << "\n=== 3D Treasure Game ===" << endl;
        cout << "1. Start Game" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nStarting the game...\n";
            game.startGame();
            break;
        case 0:
            cout << "\nExiting the game. Goodbye!" << endl;
            break;
        default:
            cout << "\nInvalid option. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
