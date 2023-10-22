#ifndef DEBUG_H
#define DEBUG_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>

class Debug
{
public:
    Debug(){
        std::cout << " WE ARE ALLS" << std::endl;
#ifdef _WIN32
        AllocConsole();
        freopen("conin$","r",stdin);
        freopen("conout$","w",stdout);
        freopen("conout$","w",stderr);
        setvbuf(stdout, NULL, _IONBF, 0);
#endif
    }

    Debug(const Debug &) = delete;

    Debug &operator=(const Debug &) = delete;

    ~Debug(){
#ifdef _WIN32
        FreeConsole();
#endif
    }
};

#endif // DEBUG_H
