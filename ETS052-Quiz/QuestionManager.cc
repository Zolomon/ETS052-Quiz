#include "QuestionManager.h"
#include <vector>
#include "Question.h"
#include <string>

using std::vector;
using std::string; 


namespace ETS052
{
    QuestionManager::QuestionManager()
    {

    }

    QuestionManager::~QuestionManager()
    {

    }

    void QuestionManager::addQuestions(vector<Question *> question)
    {
        mQuestions.push_back(question);
    }

    string QuestionManager::getCategory(int id)
    {
        return mQuestions[id][0]->getCategory();
    }

    vector<Question *> QuestionManager::getQuestionSet(int id)
    {
        return mQuestions[id];
    }
}