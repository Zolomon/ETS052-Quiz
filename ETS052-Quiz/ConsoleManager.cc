#include "ConsoleManager.h"
#include <iostream>
#include <string>
#include <Windows.h>

using std::string;
using std::cout;

namespace ETS052 
{
    ConsoleManager::ConsoleManager()
    {
#ifdef _WIN32
        // Get handles to STDIN and STDOUT.
        mHStdin = GetStdHandle(STD_INPUT_HANDLE); 
        mHStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
        if (mHStdin == INVALID_HANDLE_VALUE || 
            mHStdout == INVALID_HANDLE_VALUE) 
        {
            MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"), 
                MB_OK);
            exit(1);
        }

        SetWindowPos(GetConsoleHwnd(), HWND_TOP, 2024,0,860, 512, 0);

        // Save the current text colors. 
        if (! GetConsoleScreenBufferInfo(mHStdout, &mCsbiInfo)) 
        {
            //MessageBox(NULL, TEXT("GetConsoleScreenBufferInfo"), 
            //    TEXT("Console Error"), MB_OK); 
            exit(1);
        }
        mWOldColorAttrs = mCsbiInfo.wAttributes; 

        // Set the text attributes to draw red text on black background. 

        //if (! SetConsoleTextAttribute(mHStdout, FOREGROUND_RED | 
        //    FOREGROUND_INTENSITY))
        //{
        //    MessageBox(NULL, TEXT("SetConsoleTextAttribute"), 
        //        TEXT("Console Error"), MB_OK);
        //    exit(1);
        //}

        // Write to STDOUT and read from STDIN by using the default 
        // modes. Input is echoed automatically, and ReadFile 
        // does not return until a carriage return is typed. 
        // 
        // The default input modes are line, processed, and echo. 
        // The default output modes are processed and wrap at EOL. 
        // ....

        // Turn off the line input and echo input modes 
        if (! GetConsoleMode(mHStdin, &mFdwOldMode)) 
        {
            MessageBox(NULL, TEXT("GetConsoleMode"), TEXT("Console Error"),
                MB_OK); 
            exit(1);
        }

        mFdwMode = mFdwOldMode & 
            ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT); 
        if (! SetConsoleMode(mHStdin, mFdwMode)) 
        {
            MessageBox(NULL, TEXT("SetConsoleMode"), TEXT("Console Error"),
                MB_OK); 
            exit(1);
        }

        // ReadFile returns when any input is available.  
        // WriteFile is used to echo input. 



#else 

#endif // _WIN32        
    }

    ConsoleManager::~ConsoleManager()
    {
#ifdef _WIN32

        // Restore the original console mode. 
        SetConsoleMode(mHStdin, mFdwOldMode);

        // Restore the original text colors to keep users happy
        SetConsoleTextAttribute(mHStdout, mWOldColorAttrs);
#else

#endif // _WIN32
    }

#ifdef _WIN32
    // The NewLine function handles carriage returns when the processed 
    // input mode is disabled. It gets the current cursor position 
    // and resets it to the first cell of the next row. 

    void ConsoleManager::NewLine(void) 
    { 
        if (! GetConsoleScreenBufferInfo(mHStdout, &mCsbiInfo)) 
        {
            MessageBox(NULL, TEXT("GetConsoleScreenBufferInfo"), 
                TEXT("Console Error"), MB_OK); 
            exit(1);
        }

        mCsbiInfo.dwCursorPosition.X = 0; 

        // If it is the last line in the screen buffer, scroll 
        // the buffer up. 

        if ((mCsbiInfo.dwSize.Y-1) == mCsbiInfo.dwCursorPosition.Y) 
        { 
            ScrollScreenBuffer(mHStdout, 1); 
        } 

        // Otherwise, advance the cursor to the next line. 

        else mCsbiInfo.dwCursorPosition.Y += 1; 

        if (! SetConsoleCursorPosition(mHStdout, 
            mCsbiInfo.dwCursorPosition)) 
        {
            MessageBox(NULL, TEXT("SetConsoleCursorPosition"), 
                TEXT("Console Error"), MB_OK); 
            exit(1);
        }
    } 

    void ConsoleManager::ScrollScreenBuffer(HANDLE h, INT x)
    {
        SMALL_RECT srctScrollRect, srctClipRect;
        CHAR_INFO chiFill;
        COORD coordDest;

        srctScrollRect.Left = 0;
        srctScrollRect.Top = 1;
        srctScrollRect.Right = mCsbiInfo.dwSize.X - (SHORT)x; 
        srctScrollRect.Bottom = mCsbiInfo.dwSize.Y - (SHORT)x; 

        // The destination for the scroll rectangle is one row up. 

        coordDest.X = 0; 
        coordDest.Y = 0; 

        // The clipping rectangle is the same as the scrolling rectangle. 
        // The destination row is left unchanged. 

        srctClipRect = srctScrollRect; 

        // Set the fill character and attributes. 

        chiFill.Attributes = FOREGROUND_RED|FOREGROUND_INTENSITY; 
        chiFill.Char.AsciiChar = (char)' '; 

        // Scroll up one line. 

        ScrollConsoleScreenBuffer( 
            h,               // screen buffer handle 
            &srctScrollRect, // scrolling rectangle 
            &srctClipRect,   // clipping rectangle 
            coordDest,       // top left destination cell 
            &chiFill);       // fill character and color 
    }

    HWND ConsoleManager::GetConsoleHwnd(void)
    {
#define MY_BUFSIZE 1024 // Buffer size for console window titles.
        HWND hwndFound;         // This is what is returned to the caller.
        char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
        // WindowTitle.
        char pszOldWindowTitle[MY_BUFSIZE]; // Contains original
        // WindowTitle.

        // Fetch current window title.
        GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);

        // Format a "unique" NewWindowTitle.

        wsprintf(pszNewWindowTitle,"%d/%d",
            GetTickCount(),
            GetCurrentProcessId());

        // Change current window title.

        SetConsoleTitle(pszNewWindowTitle);

        // Ensure window title has been updated.

        Sleep(40);

        // Look for NewWindowTitle.

        hwndFound=FindWindow(NULL, pszNewWindowTitle);

        // Restore original window title.

        SetConsoleTitle(pszOldWindowTitle);

        return(hwndFound);
    }
#endif // _WIN32


    void ConsoleManager::print(string output, int color)
    {
#ifdef _WIN32
        if (! SetConsoleTextAttribute(mHStdout, color))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"), 
                TEXT("Console Error"), MB_OK);
            exit(1);
        }
        LPSTR s = const_cast<char *>(output.c_str());

        WriteFile( 
            mHStdout,               // output handle 
            s,                     // prompt string 
            lstrlenA(s),           // string length 
            &mCWritten,             // bytes written 
            NULL);
        
        
        FlushConsoleInputBuffer( mHStdin );
#else
        cout << output;
#endif // _WIN32
    }

    int ConsoleManager::read()
    {
#ifdef _WIN32
        
        ReadFile( 
            mHStdin,    // input handle 
            chBuffer,  // buffer to read into 
            1,       // size of buffer 
            &mCRead,    // actual bytes read 
            NULL);

        return atoi(&(chBuffer[0]));
#else
        int tmp;
        cin << tmp;
        return tmp;
#endif // _WIN32
        return 0;
    }
}