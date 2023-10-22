#include "ship_wig.h"
#include "player.h"

void ShipWidget::drawShips()
{
    for (auto& a: getShips()) {
        std::cout << "Drawing ship" << std::endl;
        for (auto& button: a.body){
            button->show();
        }
    }
}

void ShipWidget::fillUpShips()
{
    std::vector<ShipStruct>& ships = getShips();
    const std::vector<ShipType>& ship_types = getShipTypes();

    int start_x = 50;
    for (ShipType ship_type : ship_types)
    {
        for (int i = 0; i < ship_type.count; i++)
        {
            std::vector<QPushButton*> temp;
            for (int s = 0; s < ship_type.size; s++)
            {
                QPushButton* t = new QPushButton(QString("Button %1-%2").arg(ship_type.count).arg(ship_type.size) ,reserved);
                t->setGeometry(start_x + 50 * s, 650, 50, 50);
                t->setStyleSheet("background-color: yellow;");
                temp.push_back(t);
            }

            ships.push_back({temp});
            temp.clear();
        }
        start_x += (ship_type.size * 50) + 50;
    }
};

bool ShipWidget::canPlaceShip(int startX, int startY, Positioning relative_position, int shipLength) {
    if (relative_position == Positioning::HORIZONTAL) {
        std::cout << "Orientation: X" << std::endl;
        if ((startX + shipLength) > 10) {
            std::cout << " Ship will hit " << std::endl;
            return false;
        }

        for (int x = startX; x < startX + shipLength; x++) { // Check for collisions with other ships horizontally
            if (Player::getPrivateMatrix()[startY][x] == TileStatus::SHIP) {
                std::cout << " Ship collides with another ship " << std::endl;
                return false; // Ship collides with another ship
            }
        }

        // Check for minimal distance between ships horizontally
        for (int x = startX - 1; x < startX + shipLength + 1; ++x) {
            for (int y = startY - 1; y < startY + 1 + 1; ++y) {
                if (x >= 0 && x < 10 && y >= 0 && y < 10 && Player::getPrivateMatrix()[y][x] != TileStatus::HIDDEN) {
                    return false; // Too close to another ship
                }
            }
        }
    } else if (relative_position ==  Positioning::VERTICAL) {
        if (startY + shipLength > 10) { // Check if the ship can fit vertically
            return false; // Ship goes beyond the board's bottom edge
        }
        for (int y = startY; y < startY + shipLength; y++) {  // Check for collisions with other ships vertically
            if (Player::getPrivateMatrix()[y][startX] == TileStatus::SHIP) {
                return false; // Ship collides with another ship
            }
        }

        // Check for minimal distance between ships vertically
        for (int y = startY - 1; y < startY + shipLength + 1; ++y) {
            for (int x = startX - 1; x < startX + 1 + 1; ++x) {
                if (x >= 0 && x < 10 && y >= 0 && y < 10 && Player::getPrivateMatrix()[y][x] != TileStatus::HIDDEN) {
                    return false; // Too close to another ship
                }
            }
        }
    } else {
        return false;
    }
    std::cout << "Can place ship" << std::endl;
    return true; // Ship can be placed
}
