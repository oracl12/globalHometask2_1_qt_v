#ifndef OTHER_H
#define OTHER_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void SleepS(float seconds);

#endif // OTHER_H
