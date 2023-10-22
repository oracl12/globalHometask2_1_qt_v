#include "../headers/conf.h"

char Conf::gameMode= 'b'; // bot - b, network - n
int Conf::port = 5555;
bool Conf::host = false;
bool Conf::ready = false;
bool Conf::gameStarted = false;

bool Conf::Shared::playerStep = true;
bool Conf::Shared::pauseThread = true;
bool Conf::Shared::stopThread = false;

std::mutex Conf::Shared::stopThreadGuard;
std::mutex Conf::Shared::playerStepGuard;
std::mutex Conf::Shared::pauseThreadGuard;
