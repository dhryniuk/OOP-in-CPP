#include "headers/normal.h"


bool normal::positive_support() 
{
    return false;
}
normal::normal(double m, double s) : mean{m}, stdv{s} {
    std::normal_distribution<> dis{mean,stdv};
};
normal::~normal() {};
double normal::sample(std::mt19937 generator)
{
    return dis(generator);
}
double normal::pdf(double x)
{
    return 1.0/(stdv*pow(2.0*pi,0.5)) * 
    (exp(-0.5*(((x-mean)/stdv)*((x-mean)/stdv))));
}