#ifndef NORMAL_H 
#define NORMAL_H

#include "continuous_distribution.h"


class normal: public continuous_distribution
{
private:
    double mean, stdv;
    std::normal_distribution<double> dis{mean,stdv};
public:
    bool positive_support();
    normal(double m, double s);
    ~normal();
    double sample(std::mt19937 generator);
    double pdf(double x);
};

#endif