#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <QPushButton>
#include "ship_structs.h"

class Enemy
{
public:
    static inline TileStatus (*getPrivateMatrix())[10]
    {
        static TileStatus enemy_warship_matrix_private[10][10];
        return enemy_warship_matrix_private;
    }

    static inline std::pair<QPushButton*, TileStatus> (*getPublicMatrix())[10] {
        static std::pair<QPushButton*, TileStatus> enemy_warship_matrix_public[10][10];
        return enemy_warship_matrix_public;
    }
};

#endif // ENEMY_H
