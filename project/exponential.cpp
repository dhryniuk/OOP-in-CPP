#include "headers/exponential.h"


bool exponential::positive_support() 
{
    return true;
}
exponential::exponential(double lambda_in) : lambda{lambda_in} 
{
    std::exponential_distribution<double> dis{lambda};
};
exponential::~exponential() {};
double exponential::sample(std::mt19937 generator)
{
    return dis(generator);
}
double exponential::pdf(double x)
{
    if (x>=0) return lambda*exp(-lambda*x);
    else return 0;
}