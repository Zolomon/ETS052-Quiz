#pragma once
#include "Question.h"
#include <vector>

using std::vector;

namespace ETS052
{

class QuizSession
{
	vector<vector<Question *> > mQuestions;
public:
	QuizSession();
	~QuizSession();

	void shuffleQuestions();
	void addQuestions(vector<Question *> questions);
	Question *nextQuestion();
    vector<int> score();

    void newSession() 
    {
        throw std::exception("The method or operation is not implemented.");
    }
    void startQuiz();
    bool hasQuestions();
};

}
