#ifndef CONF_H
#define CONF_H

#include <mutex>

class Conf
{
public:
    static bool debug;
    static char gameMode;
    static int port;
    static bool host;
    static bool ready;
    static bool gameStarted;

    class Shared
    {
    public:
        static bool getPlayerStep(){
            std::lock_guard<std::mutex> lock(playerStepGuard);
            return playerStep;
        };

        static void setPlayerStep(bool newValue){
            std::lock_guard<std::mutex> lock(playerStepGuard);
            playerStep = newValue;
        };

        static bool getPauseThread(){
            std::lock_guard<std::mutex> lock(pauseThreadGuard);
            return pauseThread;
        };

        static void setPauseThread(bool newValue){
            std::lock_guard<std::mutex> lock(pauseThreadGuard);
            pauseThread = newValue;
        };

        static bool getStopThread(){
            std::lock_guard<std::mutex> lock(stopThreadGuard);
            return stopThread;
        };

        static void setStopThread(bool newValue){
            std::lock_guard<std::mutex> lock(stopThreadGuard);
            stopThread = newValue;
        };
    private:
        static bool playerStep;
        static std::mutex playerStepGuard;
        static bool pauseThread;
        static std::mutex pauseThreadGuard;
        static bool stopThread;
        static std::mutex stopThreadGuard;
    };
};

typedef Conf::Shared ConfS;

#endif // CONF_H
