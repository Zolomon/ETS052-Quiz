#pragma once 

#include <string>
#include <vector>
#include <ostream>

using std::string;
using std::vector;
using std::ostream;
using std::endl;

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
        void setAnswer(int index);
        void addOption(string option);
        void setQuestion(string question);
    };   
}

