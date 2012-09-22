#include "Question.h"

namespace ETS052
{
    ostream& operator<< (ostream &out, const Question &rhs)
    {
        int i = 0;
        string output = (rhs.mQuestion.size() < 69) ? rhs.mQuestion : rhs.mQuestion.substr(0,69);
        out << rhs.mId << " [" <<  rhs.mCategory.substr(0,10) << "] " << output << endl;
        for (auto q = rhs.mOptions.begin(); q < rhs.mOptions.end(); q++, i++)
        {
            if (i == rhs.mAnswer) 
                out << "\t ==> \t" << *q << endl;
            else
                out << "\t\t" << *q << endl;
        }
        return out;
    }

    Question::Question()
    {

    }

    Question::~Question()
    {

    }

    void Question::setId(int id)
    {
        mId = id;
    }

    void Question::setAnswer(int index)
    {
        mAnswer = index;
    }

    void Question::setCategory(string category)
    {
        mCategory = category;
    }

    void Question::setQuestion(string question)
    {
        mQuestion = question;
    }

    void Question::addOption(string option)
    {
        mOptions.push_back(option);
    }

    string Question::getCategory()
    {
        return mCategory;
    }

    string Question::getQuestion()
    {
        return mQuestion;
    }

    vector<string> Question::getOptions()
    {
        return mOptions;
    }

    pair<int, vector<string>> Question::shuffleOptions()
    {
        return make_pair(mAnswer, mOptions);
    }
}