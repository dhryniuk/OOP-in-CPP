#ifndef BINOMIAL_H 
#define BINOMIAL_H

#include "discrete_distribution.h"


class binomial: public discrete_distribution
{
private:
    int n; 
    float p;
    std::binomial_distribution<int> dis{n,p};
public:
    bool positive_support();
    binomial(int number, float success);
    ~binomial();
    int sample(std::mt19937 generator);
    double pdf(int x);
};

#endif