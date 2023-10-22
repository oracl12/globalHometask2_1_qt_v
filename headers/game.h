#ifndef GAME_H
#define GAME_H

#include <thread>
#include <iostream>

#include "conf.h"
#include "other.h"
#include "bot.h"

class Game
{
public:
    Game();

    void run();

    ~Game();

    std::thread botThread;
};

#endif // GAME_H
