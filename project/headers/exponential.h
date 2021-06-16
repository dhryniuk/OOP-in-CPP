#ifndef EXPONENTIAL_H 
#define EXPONENTIAL_H

#include "continuous_distribution.h"


class exponential: public continuous_distribution
{
private:
    double lambda;
    std::exponential_distribution<double> dis{lambda};
public:
    bool positive_support();
    exponential(double lambda_in);
    ~exponential();
    double sample(std::mt19937 generator);
    double pdf(double x);
};

#endif