#pragma once

#include <string>
#include <fstream>
#include "QuestionManager.h"

namespace ETS052
{
    class QuestionReader
    {
    public:
    	QuestionReader();
    	~QuestionReader();

        void parseQuestions(int id, QuestionManager *bank, string path);
        bool replace(std::string& str, const std::string& from, const std::string& to);
        void replaceAll(std::string& str, const std::string& from, const std::string& to);
    };
}