#pragma once 

#include <string>
#include <vector>
#include <ostream>
#include <utility>

using std::string;
using std::vector;
using std::ostream;
using std::endl;
using std::pair; 

namespace ETS052
{
    class Question
    {
        int mId;
        string mQuestion;
        int mAnswer;
        vector<string> mOptions;
        string mCategory;
    public:
        friend ostream& operator<< (ostream &out, const Question &rhs);

    	Question();
    	~Question();

        void setId(int id);
        void setCategory(string category);
        void setQuestion(string question);
        void addOption(string option);
        void setAnswer(int index);

        pair<int, vector<string>> shuffleOptions();
        string getCategory();
        string getQuestion();
        vector<string> getOptions();
        int getAnswer();
    };   
}

