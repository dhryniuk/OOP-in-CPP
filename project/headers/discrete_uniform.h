#ifndef DISCRETE_UNIFORM_H 
#define DISCRETE_UNIFORM_H

#include "discrete_distribution.h"


class discrete_uniform: public discrete_distribution
{
private:
    int min, max;
    std::uniform_int_distribution<int> dis{min,max};
public:
    bool positive_support();
    discrete_uniform(int a, int b);
    ~discrete_uniform();
    int sample(std::mt19937 generator);
    double pdf(int x);
};

#endif