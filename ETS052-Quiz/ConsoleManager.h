#ifndef CONSOLE_MANAGER_H_
#define CONSOLE_MANAGER_H_
#include <string>
#include <Windows.h>
#include <concrt.h>
#include <wincon.h>
#include <wtypes.h>

using std::string;

namespace ETS052
{
    class ConsoleManager
    {
        /* COLORS HERE */
#ifdef _WIN32
        HANDLE mHStdout, mHStdin; 
        CONSOLE_SCREEN_BUFFER_INFO mCsbiInfo; 
        CHAR chBuffer[256]; 
        DWORD mCRead, mCWritten, mFdwMode, mFdwOldMode; 
        WORD mWOldColorAttrs; 
#endif // _WIN32

    public:
        ConsoleManager();
        ~ConsoleManager();

        void print(string output, int color);
        int read(void);

#ifdef _WIN32
        void NewLine(void);
        void ScrollScreenBuffer(HANDLE h, INT x);
        HWND GetConsoleHwnd(void);
#endif
    };
}
#endif