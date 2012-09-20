#pragma once

#include <vector>
#include "Question.h"

using std::vector;
namespace ETS052
{
class QuestionManager
{
	vector<Question> mQuestions;
public:
	QuestionManager();
	~QuestionManager();

	//void shuffle();
	//void printQuestion();
	//Question getCurrentQuestion();
	//void reset();
	//bool answer(string answer);
	//void next();

    void addQuestion(Question *question);
    void clearQuestions();
protected:
	
private:
};

}