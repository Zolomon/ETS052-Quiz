#pragma once

#include <vector>
#include "Question.h"
#include <string>
#include "QuizSession.h"

using std::vector;
using std::string; 

namespace ETS052
{
class QuestionManager
{
	QuestionBank mQuestions;
public:
	QuestionManager();
	~QuestionManager();

	//void shuffle();
	//void printQuestion();
	//Question getCurrentQuestion();
	//void reset();
	//bool answer(string answer);
	//void next();

    void addQuestions(QuestionSet question);
    vector<Question *> getQuestionSet(int id);
    string getCategory(int id);

protected:
	
private:
};

}