#ifndef GAMMAD_H 
#define GAMMAD_H

#include "continuous_distribution.h"


class gammad: public continuous_distribution
{
private:
    double alpha, beta;
    std::gamma_distribution<double> dis{alpha,beta};
public:
    bool positive_support();
    gammad(double alpha_in, double beta_in);
    ~gammad();
    double sample(std::mt19937 generator);
    double pdf(double x);
};

#endif