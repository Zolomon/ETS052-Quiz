#pragma once
#include "Question.h"
#include <vector>

using std::vector;

namespace ETS052
{
    typedef vector<vector<Question *> > QuestionBank;
    typedef vector<Question *> QuestionSet;
    typedef vector<Question *>::iterator QuestionIterator;


class QuizSession
{
	QuestionBank mQuestions;
    QuestionSet mQuiz;
    QuestionIterator mQuestionIterator;
    QuestionIterator mQuestionEndIterator;
public:
	QuizSession();
	~QuizSession();

	void shuffleQuestions();
	void addQuestions(QuestionSet questions);
	Question *nextQuestion();
    vector<int> score();

    void newSession() 
    {
        throw std::exception("The method or operation is not implemented.");
    }
    void startQuiz();
    bool hasQuestions();
    size_t numberOfQuestions();
};

}
