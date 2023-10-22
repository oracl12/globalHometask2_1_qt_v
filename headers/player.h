#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <QPushButton>
#include "ship_structs.h"
#include "ship_wig.h"
#include "enemy.h"

class Player
{
public:
    static inline TileStatus (*getPrivateMatrix())[10] {
        static TileStatus player_warship_matrix_private[10][10];
        return player_warship_matrix_private;
    }

    static inline std::pair<QPushButton*, TileStatus> (*getPublicMatrix())[10] {
        static std::pair<QPushButton*, TileStatus> player_warship_matrix_public[10][10];
        return player_warship_matrix_public;
    }

    static bool makeShot(int x, int y);
    static void changeDirection(ShipStruct* ship, Positioning direction);
    static bool placeShip(int startX, int startY, ShipStruct &ship);
    static bool removeShip(int startX, int startY, ShipStruct &ship);
    static bool isShipPlacementFinished();

};

#endif // PLAYER_H
