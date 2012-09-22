#pragma once 
#include <stdlib.h>

namespace ETS052
{

class RandomInt
{
public:
    RandomInt() {}
    int operator() (int aRange)
    {
        srand(42);//seed of your choice here
        int result = rand() % aRange;
        return result;
    }
};

}