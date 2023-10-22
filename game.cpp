#include "game.h"

Game::Game()
{
    botThread = std::thread(&Game::run, this);
}

void Game::run()
{
    // network is not implement -> gamemode by defauls is b
    // when network -> make while with cond check if n or b
    std::cout << "GAMEMODE: " << Conf::gameMode << std::endl;
    if (Conf::gameMode == 'b') {
        while (true) {
            std::cout << "LOOPING" << std::endl;
            if (!Conf::Shared::pauseThread) {
                Bot::entry_point();
                std::cout << "BOT MAKE STEP" << std::endl;
                Conf::Shared::pauseThread = true;
            }
            SleepS(0.1);

            if (Conf::Shared::stopThread){
                std::cout << "STOP THREAD" << std::endl;
                break;
            }
        }
    } else if (Conf::gameMode == 'n'){
        // network stuff
    }
}

Game::~Game() {
    Conf::Shared::stopThread = true;

    if (botThread.joinable()) {
        botThread.join();
    }
    exit(1);
}
