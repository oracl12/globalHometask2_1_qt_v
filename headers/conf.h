#ifndef CONF_H
#define CONF_H

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
        static bool playerStep;
        static bool pauseThread;
        static bool stopThread;
        // maybe add methods to get it with already mutex
    };
};

#endif // CONF_H
