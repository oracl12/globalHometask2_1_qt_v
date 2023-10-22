#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QStyleFactory>

#include "game.h"

// make mutex on all getters from conf shared
// fix why bot is shooting in mirror
// update bot as in v1 of project

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    MainWindow w;

    w.setFixedSize(1280, 720);

    Game game;

    w.show();
    return a.exec();
}
