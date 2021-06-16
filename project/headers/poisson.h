#ifndef POISSON_H 
#define POISSON_H

#include "discrete_distribution.h"


class poisson: public discrete_distribution
{
private:
    double lambda;
    std::poisson_distribution<int> dis{lambda};
public:
    bool positive_support();
    poisson(double lambda_in);
    ~poisson();
    int sample(std::mt19937 generator);
    double pdf(int k);
};

#endif