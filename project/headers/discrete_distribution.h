#ifndef DISCRETE_DISTRIBUTION_H 
#define DISCRETE_DISTRIBUTION_H

#include "distribution.h"


class discrete_distribution: public distribution
{
public:
    virtual bool positive_support()=0;
    virtual ~discrete_distribution() {};
    virtual int sample(std::mt19937 generator)=0;
    virtual double pdf(int k)=0;
};

#endif