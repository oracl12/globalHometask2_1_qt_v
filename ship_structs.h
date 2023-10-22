#ifndef SHIP_STRUCTS_H
#define SHIP_STRUCTS_H

#include <QPushButton>

struct ShipType
{
    int size;
    int count;
};

enum class Positioning{
    VERTICAL,
    HORIZONTAL
};

struct ShipStruct
{
    std::vector<QPushButton*> body;
    Positioning relative_position = Positioning::HORIZONTAL;
    bool avaible = true;
    struct {
        int x;
        int y;
    } placeOnMatrix = { -1, -1 }; // head on matrix
};

enum class TileStatus
{
    CLEARED = -1,
    HIDDEN = 0,
    SHOTTEN = 1,
    SHIP = 2
};

#endif // SHIP_STRUCTS_H
