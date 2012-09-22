#include <iostream>
#include <windows.h>
#include "ConsoleManager.h"
#include "QuestionReader.h"
#include "QuizSession.h"
#include "QuestionManager.h"
#include <sstream>
#include <map>
#include <algorithm>
#include <locale>

using namespace std;
using namespace ETS052;

ConsoleManager cm;
QuestionManager qm;

void Header() 
{
    cm.clearScreen();
    cm.print("                       ", 204);
    cm.print(" ETS052 - Computer Communication ", 249);
    cm.print("                       ", 204);
    cm.print("\n", 0);
}

int DrawMenu() 
{
    Header();

    cm.print("\n", 0);
    cm.print("\n", 0);
    cm.print("\n", 0);

    cm.print("                       ", 17);
    cm.print(" MENU ", 249);
    cm.print("                       ", 17); cm.print("\n", 0);
    cm.print("                       ", 0);
    cm.print("[ 0 ] ", 10); cm.print("New Session", 7); cm.print("\n", 0);
    cm.print("                       ", 0);
    cm.print("[ 1 ] ", 10); cm.print("Quit", 7); cm.print("\n", 0);

    return cm.read();
}

void ReadQuestions( QuizSession qs ) 
{
    QuestionReader qr;
    for (int i = 1; i < 33; i++)
    {
        stringstream ss;
        ss << "questions/" << i << ".txt";
        cm.print("Parsing..." + ss.str(), 128);
        qr.parseQuestions(i, &qm, ss.str());
    }
}

void PrintCategories(map<int, string> &chosenCategories, map<int, string> &selectableCategories) 
{
    cm.print("Selected Categories\n", 154);

    for (auto it = chosenCategories.begin(); it != chosenCategories.end(); it++)
    {
        stringstream ss;
        ss << it->first;
        if (it->first < 10)
            cm.print("[ ", 122);
        else 
            cm.print("[", 122);
        cm.print(ss.str(), 127);
        cm.print("]", 122);
        cm.print(" ", 135);
        cm.print(it->second, 135);
        cm.print("\n", 0);
    }

    cm.print("Selectable Categories\n", 154);

    for (auto it = selectableCategories.begin(); it != selectableCategories.end(); it++)
    {
        stringstream ss;
        ss << it->first;
        if (it->first < 10)
            cm.print("[ ", 122);
        else 
            cm.print("[", 122);
        cm.print(ss.str(), 127);
        cm.print("]", 122);
        cm.print(" ", 135);
        cm.print(it->second, 135);
        cm.print("\n", 0);
    }
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int SelectChapters( QuizSession qs ) 
{
    Header();

    map<int, string> chosenCategories;
    map<int, string> selectableCategories;

    for (int i = 0; i < 32; i++)
    {
        selectableCategories[i] = qm.getCategory(i);
    }

    string *res;
    while(true)
    {
        PrintCategories(chosenCategories, selectableCategories);

        cm.print("Type number followed by enter to select a chapter:", 127);

        res = cm.readLine();

        if (is_number(*res))
        {
            int id = atoi(res->c_str());
            if (id >= 0 && id <= 32)
            {
                auto c = selectableCategories.find(id);
                if (c != selectableCategories.end())
                {
                    chosenCategories[c->first] = c->second;
                    selectableCategories.erase(c);
                }
                else
                {
                    c = chosenCategories.find(id);
                    if (c != chosenCategories.end())
                    {
                        selectableCategories[c->first] = c->second;
                        chosenCategories.erase(c);
                    }
                    else
                    {
                        cout << "COCOCOCOCOCOMBOBREAKER" << endl;
                    }
                }
                
            }
        }
        else
        {
            if (res->compare("c") == 0)
            {
                return -1;
            }
            else if (res->compare("s"))
            {
                return 1;
            }
            
        }

        delete res;
    }
}

void DoQuiz( QuizSession qs ) 
{
    throw std::exception("The method or operation is not implemented.");
}

void PrintResult( QuizSession qs ) 
{
    throw std::exception("The method or operation is not implemented.");
}

void RepeatQuizOrQuit( QuizSession qs ) 
{
    throw std::exception("The method or operation is not implemented.");
}

void NewSession() 
{
    QuizSession qs;
    ReadQuestions(qs);
    int res = SelectChapters(qs);
    if (res == -1)
    {
        exit(0);
    }
    else 
    {
        DoQuiz(qs);
        PrintResult(qs);
        RepeatQuizOrQuit(qs);
    }
}



int main()
{
//    HANDLE hConsole;
//    int k;

//    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // you can loop k higher to see more color choices
    //for(k = 1; k < 255; k++)
    //{
    //    // pick the colorattribute k you want
    //    SetConsoleTextAttribute(hConsole, k);
    //    cout << k << " I want to be nice today!" << endl;
    //}
    
    //QuestionReader qr;
    //qr.parseQuestions(1, &qm, "questions/1.txt");

    //cm.clearScreen();

    while (true)
    {
        char res = DrawMenu();

        /*QuestionManager qm;
        QuestionReader qr;
        qr.parseQuestions(&qm, "questions/1.txt");*/

        if (res == '0') {
            NewSession();
        }

        if (res == 1)
            break;
    }
    return 0;
}