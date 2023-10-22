#ifndef BOT_H
#define BOT_H

#include "enemy.h"
#include "ship_structs.h"

class Bot : public Enemy
{
public:
    static void entry_point();

    static bool makeShot(int x, int y);

    static void generateShipsOnMatrix();

private:
    static bool shootOneOfFourClosesTile();

    static bool hasMinimumDistance(int x, int y, int size, int orientation);

    static void placeShip(int size, int orientation, int x, int y);
};
#endif // BOT_H
