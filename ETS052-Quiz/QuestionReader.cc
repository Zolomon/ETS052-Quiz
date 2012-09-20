#pragma once

#include "QuestionReader.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using std::stringstream;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

namespace ETS052
{
    QuestionReader::QuestionReader()
    {

    }
    QuestionReader::~QuestionReader()
    {

    }

    bool QuestionReader::replace(std::string& str, const std::string& from, const std::string& to) {
        size_t start_pos = str.find(from);
        if(start_pos == std::string::npos)
            return false;
        str.replace(start_pos, from.length(), to);
        return true;
    }

    void QuestionReader::replaceAll(std::string& str, const std::string& from, const std::string& to) {
        if(from.empty())
            return;
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
    }

    void QuestionReader::parseQuestions(QuestionManager *bank, string path)
    {
        ifstream file;
        file.open(path);
        int count = 0;
        string line;
        string title;
        string question;
        string option;
        if (file.is_open())
        {
            if (!file.eof())
            {
                getline(file,title);
                //cout << "Title read: " << title << endl;
            }
            while(!file.eof())
            {
                cout << "Reading question: " << count++ << endl;
                Question q;
                q.setCategory(title);
                getline(file, question);

                replace(question, "\tINCORRECT\t\t", "  ");
                replace(question, "\tCORRECT\t\t", "  ");

                cout << "Question read: "<< question << endl;

                q.setId(count);

                question.replace(0,3, "");
                replaceAll(question, "\t", "");

                cout << "Question read: \""<< question << "\"" << endl;
                q.setQuestion(question);
                for (int j = 0; j < 4; j++)
                {
                    getline(file, option);
                    
                   while(option.find("\t\t\t\t\t\t") != string::npos)
                    {
                        getline(file, option);
                    }

                    cout << "Option read: "<< option << endl;
                    if (option.find("\t\t\tcorrect\t\t") != string::npos)
                    {
                            q.setAnswer(j);
                            cout << "Correct answer: " << j << endl;
                            replace(option, "\t\t\tcorrect\t\t", "");
                    }

                    replace(option, "\t\t\t\t\t", "");
                    cout << "Option read: " << option.c_str() << endl;                   

                    q.addOption(option);
                }

                while(option.find("\t\t\t\t\t\t") != string::npos)
                {
                    getline(file, line);
                }
                
                cout << endl << endl << q << endl;
                //mBank->addQuestion();      
                break;
            }
        }

        file.close();
    }  
}