#include "headers/student_t.h"


bool student_t::positive_support() 
{
    return false;
}
student_t::student_t(double alpha_in) : alpha{alpha_in} 
{
    std::student_t_distribution<double> dis{alpha};
}
student_t::~student_t() {};
double student_t::sample(std::mt19937 generator)
{
    return dis(generator);
}
double student_t::pdf(double x)
{
    return 1/pow(alpha*pi, 0.5) * tgamma((alpha+1)/2)/tgamma(alpha/2) * 
    pow(1+x*x/alpha, -(alpha+1)/2);
}