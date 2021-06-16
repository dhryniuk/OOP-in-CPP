#ifndef STUDENT_T_H 
#define STUDENT_T_H

#include "continuous_distribution.h"


class student_t: public continuous_distribution
{
private:
    double alpha;
    std::student_t_distribution<double> dis{alpha};
public:
    bool positive_support();
    student_t(double alpha_in);
    ~student_t();
    double sample(std::mt19937 generator);
    double pdf(double x);
};

#endif