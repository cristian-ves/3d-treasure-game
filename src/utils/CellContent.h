#ifndef CELL_CONTENT
#define CELL_CONTENT

#include <iostream>

using namespace std;

struct CellContent
{
    enum Type {EMPTY, PLAYER, TREASURE, ENEMY, TRAP, HINT, POTION};
    enum Hint {NONE, CALIENTE, FRIO, TIBIO};

    Type type = EMPTY;
    Hint hint = NONE;

    static string getHintText(Hint hint) {
        const string hintNames[] = { "None", "Caliente", "Frio", "Tibio" };
        return hintNames[hint];
    }

    static string getTypeText(Type type) {
        const string typeNames[] = { "Empty", "Player", "Treasure", "Enemy", "Trap", "Hint", "Potion" };
        return typeNames[type];
    }
};

#endif