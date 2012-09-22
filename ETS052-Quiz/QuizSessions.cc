#include "QuizSession.h"
#include <algorithm>

namespace ETS052
{
     QuizSession::QuizSession()
     {

     }
     QuizSession::~QuizSession()
     {

     }

     void QuizSession::addQuestions(QuestionSet questions)
     {
         mQuestions.push_back(questions);
     }

     void QuizSession::shuffleQuestions()
     {
         random_shuffle(mQuiz.begin(), mQuiz.end());
         int i = 0;
         for (auto it = mQuiz.begin(); it != mQuiz.end(); it++)
         {
             (*it)->setId(i++);
         }
     }

     Question *QuizSession::nextQuestion()
     {
        Question *q = *mQuestionIterator;
        mQuestionIterator++;
        return q;

         return NULL;
     }

     void QuizSession::startQuiz()
     {
         // Clear quiz set, fill with selected questions.
         mQuiz.clear();

         for (auto it = mQuestions.begin(); it != mQuestions.end(); it++)
         {
             mQuiz.insert(mQuiz.end(), it->begin(), it->end());
         }

         // Update iterators
         mQuestionIterator = mQuiz.begin();
         mQuestionEndIterator = mQuiz.end();

         // Shuffle the quiz! 
         shuffleQuestions();
     }

     bool QuizSession::hasQuestions()
     {
         return mQuestionIterator != mQuestionEndIterator;
     }


}