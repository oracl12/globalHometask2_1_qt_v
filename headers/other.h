#ifndef OTHER_H
#define OTHER_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

inline void SleepS(float seconds)
{
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
}
#endif // OTHER_H
