#ifndef CONTINUOUS_DISTRIBUTION_H 
#define CONTINUOUS_DISTRIBUTION_H

#include "distribution.h"


class continuous_distribution: public distribution
{
public:
    virtual bool positive_support()=0;
    virtual ~continuous_distribution() {};
    virtual double sample(std::mt19937 generator)=0;
    virtual double pdf(double x)=0;
};

#endif