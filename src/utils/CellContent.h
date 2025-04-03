#ifndef CELL_CONTENT
#define CELL_CONTENT

#include <iostream>

using namespace std;

struct CellContent
{
    enum Type {EMPTY, PLAYER, TREASURE, ENEMY, TRAP, HINT, POTION};
    enum Hint {NONE, HOT, WARM, COLD};

    Type type = EMPTY;
    Hint hint = NONE;

    static string getHintText(const Hint hint) {
        const string hintNames[] = { "None", "Hot", "Warm", "Cold" };
        return hintNames[hint];
    }

    static string getTypeText(const Type type) {
        const string typeNames[] = { "Empty", "Player", "Treasure", "Enemy", "Trap", "Hint", "Potion" };
        return typeNames[type];
    }
};

#endif