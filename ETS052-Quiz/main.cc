#include <iostream>
#include <windows.h>
#include "ConsoleManager.h"
#include "QuestionReader.h"

using namespace std;
using namespace ETS052;



    int main()
    {
        //HANDLE hConsole;
        //int k;

        //hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        //// you can loop k higher to see more color choices
        //for(k = 1; k < 255; k++)
        //{
        //    // pick the colorattribute k you want
        //    SetConsoleTextAttribute(hConsole, k);
        //    cout << k << " I want to be nice today!" << endl;
        //}

        ConsoleManager cm;
        cm.print("Test", 19);

        QuestionManager qm;
        QuestionReader qr;
        qr.parseQuestions(&qm, "1.txt");

        cin.get();

        return 0;
    }