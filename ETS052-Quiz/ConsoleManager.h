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
    enum ColorCode
    {
        DarkBlack = 0,
        DarkBlue = 1,
        DarkGreen = 2,
        DarkCyan = 3,
        DarkRed = 4,
        DarkMagenta = 5,
        DarkYellow = 6,
        DarkWhite = 7,
        Black = 8,
        Blue = 9,
        Green = 10,
        Cyan = 11,
        Red = 12,
        Magenta = 13,
        Yellow = 14,
        White = 15,
    };

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

        void print(string output);
        void print(string output, int color);
        void print(string output, int bg, int fg);

        char read();
        string *readLine();

#ifdef _WIN32
        void NewLine(void);
        void ScrollScreenBuffer(HANDLE h, INT x);
        HWND GetConsoleHwnd(void);
        void clearScreen();
#endif
    };
}
#endif