#ifndef UNIFORM_H 
#define UNIFORM_H

#include "continuous_distribution.h"


class uniform: public continuous_distribution
{
private:
    double min, max;
    std::uniform_real_distribution<double> dis{min,max};
public:
    bool positive_support();
    uniform(double a, double b);
    ~uniform();
    double sample(std::mt19937 generator);
    double pdf(double x);
};

#endif