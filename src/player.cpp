#include "../headers/player.h"

bool Player::placeShip(int startX, int startY, ShipStruct &ship) {
    int shipLength = ship.body.size();
    int counter = 0;

    if (ShipWidget::canPlaceShip(startX, startY, ship.relative_position, shipLength)) {
        ship.placeOnMatrix = { startX, startY };
        if (ship.relative_position == Positioning::HORIZONTAL) {
            for (int x = startX; x < startX + shipLength; ++x) {
                getPrivateMatrix()[startY][x] = TileStatus::SHIP;
                getPublicMatrix()[x][startY].first->setStyleSheet("background-color: blue;");
                getPublicMatrix()[startX][startY].second = TileStatus::SHIP;
                counter++;
            }
        } else if (ship.relative_position == Positioning::VERTICAL) {
            for (int y = startY; y < startY + shipLength; ++y) {
                getPrivateMatrix()[y][startX] = TileStatus::SHIP;
                getPublicMatrix()[startX][y].first->setStyleSheet("background-color: blue;");
                getPublicMatrix()[startX][y].second = TileStatus::SHIP;
                counter++;
            }
        }
        for (auto& button: ship.body) {
            button->hide();
        }
        ship.avaible = false;

        std::cout << "PLACED SHIP" << std::endl;
        return true;
    }
    std::cout << "Cannot place" << std::endl;
    return false;
}

bool Player::removeShip(int startX, int startY, ShipStruct &ship) {
    if (getPrivateMatrix()[startY][startX] != TileStatus::SHIP){
        return false;
    }

    int shipLength = ship.body.size();
    if (ship.relative_position == Positioning::HORIZONTAL) {
        for (int x = ship.placeOnMatrix.x; x < ship.placeOnMatrix.x + shipLength; ++x) {
            getPrivateMatrix()[startY][x] = TileStatus::HIDDEN; // Clear the cell
            getPublicMatrix()[x][startY].first->setStyleSheet("background-color: gray;");
        }
    } else if (ship.relative_position == Positioning::VERTICAL) {
        for (int y = ship.placeOnMatrix.y; y < ship.placeOnMatrix.y + shipLength; ++y) {
            getPrivateMatrix()[y][startX] = TileStatus::HIDDEN; // Clear the cell
            getPublicMatrix()[startX][y].first->setStyleSheet("background-color: gray;");
        }
    }
    std::cout << "Removed ship" << std::endl;
    for (auto& button: ship.body) {
        button->show();
    }

    std::cout << "Showing ship again" << std::endl;
    ship.avaible = true;
    return true;
}

void Player::changeDirection(ShipStruct* ship, Positioning direction) {
    std::cout << "Change direction" << std::endl;
    if (direction == ship->relative_position) {
        std::cout << "INstA RETURN" << std::endl;
        return;
    }

    auto getShipB = [](auto ship, int index) { return ship->body[index]; };
    auto getShipBPos = [](auto ship, int index) { return ship->body[index]->pos(); };

    if (ship->relative_position == Positioning::HORIZONTAL) {
        std::cout << "Changing to vertical" << std::endl;
        int currentY = getShipBPos(ship, 0).y();
        for (int i = 0; i < ship->body.size(); ++i) {
            getShipB(ship, i)->setGeometry(
                getShipBPos(ship, 0).x(),  currentY, 50, 50
            );

            currentY += 50;
        }
        ship->relative_position = Positioning::VERTICAL;

    } else if (ship->relative_position == Positioning::VERTICAL) {
        std::cout << "Changing to horizontal" << std::endl;
        int currentX = getShipBPos(ship, 0).x();
        for (int i = 0; i < ship->body.size(); ++i) {
            getShipB(ship, i)->setGeometry(
                currentX,  getShipBPos(ship, 0).y(), 50, 50
            );

            currentX += 50;
        }

        ship->relative_position = Positioning::HORIZONTAL;
    }
}

bool Player::makeShot(int x, int y)
{
    std::cout << "Player making shot" << std::endl;
    if (x >= 0 && x < 10 && y >= 0 && y < 10)
    {
        if (Enemy::getPrivateMatrix()[x][y] == TileStatus::SHIP)
        {
            Enemy::getPublicMatrix()[x][y].second = TileStatus::SHOTTEN;
            Enemy::getPublicMatrix()[x][y].first->setStyleSheet("background-color: red;");
            Enemy::getPrivateMatrix()[x][y] = TileStatus::SHOTTEN;
            std::cout << "Player: Shot successful!" << std::endl;
            return true;
        }
        else
        {
            Enemy::getPublicMatrix()[x][y].second = TileStatus::CLEARED;
            Enemy::getPublicMatrix()[x][y].first->setStyleSheet("background-color: gray;");
            std::cout << "Player: Shot missed!" << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Player: Invalid coordinates. Shot cannot be made." << std::endl;
        return false;
    }
}

bool Player::isShipPlacementFinished(){
    for (const ShipStruct& ship : ShipWidget::getShips())
    {
        if (ship.avaible){
            return false;
        }
    }

    return true;
}
