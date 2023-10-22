#ifndef SHIP_WIG_H
#define SHIP_WIG_H

#include "ship_structs.h"

#include <vector>
#include <QPushButton>
#include <QtWidgets>
#include <iostream>

class ShipWidget: public QWidget
{
    Q_OBJECT
private:
    QWidget* reserved;
    bool isDragging;

public:

    ShipWidget(QWidget *parent = nullptr) : QWidget(parent){
        reserved = parent;
    };

    void drawShips();
    void fillUpShips();

    static bool IsMouseInButton(int mouseX, int mouseY, int buttonX, int buttonY) {
        std::cout << mouseX << " " <<  mouseY << std::endl;
        std::cout << buttonX << " " <<  buttonY << std::endl;
        return (mouseX >= (buttonX - 20) && mouseX <= (buttonX + 60) &&
                mouseY >= (buttonY - 20) && mouseY <= (buttonY + 60));
    }

    static ShipStruct* findShipByMouse(int mouseX, int mouseY) {
        auto& ships = getShips();
        for (ShipStruct& ship : ships) {
            for (const auto& button : ship.body) {
                 if (IsMouseInButton(mouseX, mouseY, button->x(), button->y())) {
                    std::cout << "Ship: ship found and it is: " << ship.body.size() << std::endl;
                    return &ship;
                }
            }
        }
        qDebug() << "No ship found ";
        return nullptr;
    }

    static bool canPlaceShip(int startX, int startY, Positioning relative_position, int shipLength);

    static std::vector<ShipStruct> &getShips(){
        static std::vector<ShipStruct> ships;
        return ships;
    };

    static const std::vector<ShipType> &getShipTypes(){
        static const std::vector<ShipType> shipTypes = {
            {5, 1}, // One 5-rectangle ship
            {4, 2}, // Two 4-rectangle ships
            {2, 3}, // Three 2-rectangle ships
            {1, 5} // Five 1-rectangle ships
        };
        return shipTypes;
   };
};

#endif // SHIP_WIG_H
