#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "QDebug"
#include <QIntValidator>
#include <QMessageBox>
#include <QGridLayout>

#include "headers/conf.h"
#include "headers/ship_wig.h"
#include "headers/ship_structs.h"
#include "headers/player.h"
#include "headers/bot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
private slots:
    void on_continueBotButton_clicked();

    void on_continueNetButton_clicked();

    void on_submitNetButton_clicked();

    void createBlackButtonMatrix();

    void on_pushButton_clicked();

    void handleEnemyMatrixButtonClick();
private:
    Ui::MainWindow *ui;
};


class MouseReleaseFilter : public QObject {
    Q_OBJECT

protected:
    bool eventFilter(QObject *watched, QEvent *event) override {
        static int mouseX, mouseY;

        if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            int currentPosX = mouseEvent->pos().x();
            int currentPosY = mouseEvent->pos().y();
            mouseX = currentPosX;
            mouseY = currentPosY;
            return false;
        }

        if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            qDebug() << "MouseButtonRelease was released";
            if (mouseEvent->button() == Qt::LeftButton) {
                qDebug() << "Lbutton was released";
            } else if (mouseEvent->button() == Qt::RightButton) {
                qDebug() << "RButton was released";

                int currentPosX = mouseEvent->pos().x();
                int currentPosY = mouseEvent->pos().y();
                mouseX = currentPosX;
                mouseY = currentPosY;
                if (currentPosX < 50 || currentPosX > 550 || currentPosY < 50 || currentPosY > 550 ){
                    std::cout << "WE ARE NO IN a MATriX" << std::endl;
                    return 0;
                }
                int x = (int)((mouseEvent->pos().x() - 50) / 50);
                int y = (int)((mouseEvent->pos().y() - 20) / 50);
                ShipStruct* ship = ShipWidget::findShipByMouse(currentPosX, currentPosY);
                std::cout << "x: " << x << " y: " << y << std::endl;
                Player::placeShip(x, y, *ship);
            }

            if (mouseEvent->button() == Qt::MiddleButton) {
                qDebug() << "Middle was released";

                int currentPosX = mouseEvent->pos().x();
                int currentPosY = mouseEvent->pos().y();
                if (currentPosX < 50 || currentPosX > 550 || currentPosY < 50 || currentPosY > 550 ){
                    std::cout << "WE ARE NO IN a MATriX" << std::endl;
                    return 0;
                }
                int x = (int)((mouseEvent->pos().x() - 50) / 50);
                int y = (int)((mouseEvent->pos().y() - 20) / 50);
                ShipStruct* ship = ShipWidget::findShipByMouse(currentPosX, currentPosY);
                std::cout << "x: " << x << " y: " << y << std::endl;
                Player::removeShip(x, y, *ship);
            }
        }

        if (event->type() == QEvent::KeyPress) {
            std::cout << "WE PRESSED KEY" << std::endl;
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            ShipStruct* ship = ShipWidget::findShipByMouse(mouseX, mouseY);
            if (ship == nullptr) {
                std::cout << "there is no ship" << std::endl;
                return false;
            }
             if (keyEvent->key() == Qt::Key_W || keyEvent->key() == Qt::Key_S) {
                 std::cout << "UP or DOWN" << std::endl;
                Player::changeDirection(ship, Positioning::VERTICAL);
            } else if (keyEvent->key() == Qt::Key_A || keyEvent->key() == Qt::Key_D) {
                std::cout << "L or R" << std::endl;
                Player::changeDirection(ship, Positioning::HORIZONTAL);
            }
        }


        return false;
    }
};

#endif // MAINWINDOW_H
